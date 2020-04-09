#include "PPU.h"
#include <stdlib.h>
#include <string.h>
#include "palScreen.h"
#include "../../car/core/Cartridge.h"

PPU* ppu_init(Cartridge** car)
{
	PPU* ppu = (PPU*)malloc(sizeof(PPU));
	if (ppu == NULL)
		return NULL;
	memset(ppu, 0x00, sizeof(PPU));
	ppu->screen = (uint32_t*)malloc(sizeof(uint32_t) * 256 * 240);
	if (ppu->screen == NULL)
	{
		free(ppu);
		return NULL;
	}
	memset(ppu->screen, 0x00, sizeof(uint32_t) * 256 * 240);
	ppu->bus = ppu_bus_init(car);
	if (ppu->bus == NULL)
	{
		free(ppu->screen);
		free(ppu);
		return NULL;
	}
	ppu->car = car;
	return ppu;
}

void ppu_destroy(PPU* ppu)
{
	if (ppu == NULL)
		return;
	ppu_bus_destroy(ppu->bus);
	free(ppu->screen);
	free(ppu);
}

uint8_t ppu_read(PPU* ppu, uint16_t addr)
{
	uint8_t data = 0x00;
	switch (addr)
	{
	case 0x0000: // Control
	case 0x0001: // Mask
		break;
	case 0x0002: // Status
		data = (ppu->status.reg & 0xE0) | (ppu->ppu_data_buffer & 0x1F);
		ppu->status.vertical_blank = 0;
		ppu->address_latch = 0;
		break;
	case 0x0003: // OAM Address
	case 0x0004: // OAM Data
	case 0x0005: // Scroll
	case 0x0006: // PPU Address
		break;
	case 0x0007: // PPU Data
		data = ppu->ppu_data_buffer;
		ppu->ppu_data_buffer = ppu_bus_read(ppu->bus, ppu->vram_addr.reg);
		if (ppu->vram_addr.reg >= 0x3F00) 
			data = ppu->ppu_data_buffer;
		ppu->vram_addr.reg += (ppu->control.increment_mode ? 32 : 1);
		break;
	default:
		break;
	}
	return data;
}

void ppu_write(PPU* ppu, uint16_t addr, uint8_t value)
{
	switch (addr)
	{
	case 0x0000: // Control
		ppu->control.reg = value;
		ppu->tram_addr.nametable_x = ppu->control.nametable_x;
		ppu->tram_addr.nametable_y = ppu->control.nametable_y;
		break;
	case 0x0001: // Mask
		ppu->bus->mask.reg = value;
		break;
	case 0x0002: // Status
	case 0x0003: // OAM Address
	case 0x0004: // OAM Data
		break;
	case 0x0005: // Scroll
		if (ppu->address_latch == 0)
		{
			ppu->fine_x = value & 0x07;
			ppu->tram_addr.coarse_x = value >> 3;
			ppu->address_latch = 1;
		}
		else
		{
			ppu->tram_addr.fine_y = value & 0x07;
			ppu->tram_addr.coarse_y = value >> 3;
			ppu->address_latch = 0;
		}
		break;
	case 0x0006: // PPU Address
		if (ppu->address_latch == 0)
		{
			ppu->tram_addr.reg = (uint16_t)((value & 0x3F) << 8) | (ppu->tram_addr.reg & 0x00FF);
			ppu->address_latch = 1;
		}
		else
		{
			ppu->tram_addr.reg = (ppu->tram_addr.reg & 0xFF00) | value;
			ppu->vram_addr = ppu->tram_addr;
			ppu->address_latch = 0;
		}
		break;
	case 0x0007: // PPU Data
		ppu_bus_write(ppu->bus, ppu->vram_addr.reg, value);
		ppu->vram_addr.reg += (ppu->control.increment_mode ? 32 : 1);
		break;
	default:
		return;
	}
}


void ppu_tick(PPU * ppu)
{
	ppu->bus->mask.render_background = 1;
	if (ppu->scanline >= -1 && ppu->scanline < 240)
	{
		if (ppu->scanline == 0 && ppu->cycle == 0)
			ppu->cycle = 1;
		if (ppu->scanline == -1 && ppu->cycle == 1)
			ppu->status.vertical_blank = 0;
		if ((ppu->cycle >= 2 && ppu->cycle < 258) || (ppu->cycle >= 321 && ppu->cycle < 338))
		{
			ppu_update_shifters(ppu); 
			switch ((ppu->cycle - 1) % 8)
			{
			case 0:
				ppu_load_background_shifters(ppu);
				ppu->bg_next_tile_id = ppu_bus_read(ppu->bus, 0x2000 | (ppu->vram_addr.reg & 0x0FFF));
				break; 
			case 2:
				ppu->bg_next_tile_attrib = ppu_bus_read(ppu->bus,
					0x23C0 
					| (ppu->vram_addr.nametable_y << 11)
					| (ppu->vram_addr.nametable_x << 10)
					| ((ppu->vram_addr.coarse_y >> 2) << 3)
					| (ppu->vram_addr.coarse_x >> 2));
				if (ppu->vram_addr.coarse_y & 0x02) 
					ppu->bg_next_tile_attrib >>= 4;
				if (ppu->vram_addr.coarse_x & 0x02) 
					ppu->bg_next_tile_attrib >>= 2;
				ppu->bg_next_tile_attrib &= 0x03;
				break;
			case 4:
				ppu->bg_next_tile_lsb = ppu_bus_read(ppu->bus, (ppu->control.pattern_background << 12) + ((uint16_t)ppu->bg_next_tile_id << 4) + (ppu->vram_addr.fine_y) + 0);

				break;
			case 6:
				ppu->bg_next_tile_msb = ppu_bus_read(ppu->bus, (ppu->control.pattern_background << 12) + ((uint16_t)ppu->bg_next_tile_id << 4) + (ppu->vram_addr.fine_y) + 8);
				break;
			case 7:
				ppu_increment_scroll_x(ppu);
				break;
			}
		}

		if (ppu->cycle == 256)
			ppu_increment_scroll_y(ppu);
		if (ppu->cycle == 257)
		{
			ppu_load_background_shifters(ppu);
			ppu_transfer_address_x(ppu);
		}
		if (ppu->cycle == 338 || ppu->cycle == 340)
			ppu->bg_next_tile_id = ppu_bus_read(ppu->bus, 0x2000 | (ppu->vram_addr.reg & 0x0FFF));
		if (ppu->scanline == -1 && ppu->cycle >= 280 && ppu->cycle < 305)
			ppu_transfer_address_y(ppu);
	}
	if (ppu->scanline >= 241 && ppu->scanline < 261)
	{
		if (ppu->scanline == 241 && ppu->cycle == 1)
		{
			ppu->status.vertical_blank = 1;
			if (ppu->control.enable_nmi)
				ppu->nmi = TRUE;
		}
	}
	uint8_t bg_pixel = 0x00;
	uint8_t bg_palette = 0x00;
	if (ppu->bus->mask.render_background)
	{
		uint16_t bit_mux = 0x8000 >> ppu->fine_x;

		uint8_t p0_pixel = (ppu->bg_shifter_pattern_lo & bit_mux) > 0;
		uint8_t p1_pixel = (ppu->bg_shifter_pattern_hi & bit_mux) > 0;

		bg_pixel = (p1_pixel << 1) | p0_pixel;

		uint8_t bg_pal0 = (ppu->bg_shifter_attrib_lo & bit_mux) > 0;
		uint8_t bg_pal1 = (ppu->bg_shifter_attrib_hi & bit_mux) > 0;
		bg_palette = (bg_pal1 << 1) | bg_pal0;
	}
	uint32_t color = ppu_get_color_from_palette_ram(ppu, bg_palette, bg_pixel);
	ppu_set_pixel(ppu, ppu->cycle - 1, ppu->scanline, color);

	ppu->frame = FALSE;
	ppu->cycle++;
	if (ppu->cycle >= 341)
	{
		ppu->cycle = 0;
		ppu->scanline++;
		if (ppu->scanline >= 261)
		{
			ppu->scanline = -1;
			ppu->frame = TRUE;
		}
	}
}

void ppu_update_shifters(PPU* ppu)
{
	if (ppu->bus->mask.render_background)
	{
		ppu->bg_shifter_attrib_lo <<= 1;
		ppu->bg_shifter_attrib_hi <<= 1;
		ppu->bg_shifter_attrib_lo <<= 1;
		ppu->bg_shifter_attrib_hi <<= 1;
	}
}

void ppu_load_background_shifters(PPU* ppu)
{
	ppu->bg_shifter_pattern_lo = (ppu->bg_shifter_pattern_lo & 0xFF00) |   ppu->bg_next_tile_lsb;
	ppu->bg_shifter_pattern_hi = (ppu->bg_shifter_pattern_hi & 0xFF00) |   ppu->bg_next_tile_msb;
	ppu->bg_shifter_attrib_lo  = (ppu->bg_shifter_attrib_lo  & 0xFF00) | ((ppu->bg_next_tile_attrib & 0b01) ? 0xFF : 0x00);
	ppu->bg_shifter_attrib_hi  = (ppu->bg_shifter_attrib_hi  & 0xFF00) | ((ppu->bg_next_tile_attrib & 0b10) ? 0xFF : 0x00);
}

void ppu_increment_scroll_x(PPU* ppu)
{
	if (ppu->bus->mask.render_background || ppu->bus->mask.render_sprites)
	{
		if (ppu->vram_addr.coarse_x == 31)
		{
			ppu->vram_addr.coarse_x = 0;
			ppu->vram_addr.nametable_x = ~(ppu->vram_addr.nametable_x);
		}
		else
			ppu->vram_addr.coarse_x++;
	}
}

void ppu_increment_scroll_y(PPU* ppu)
{
	if (ppu->bus->mask.render_background || ppu->bus->mask.render_sprites)
	{
		if (ppu->vram_addr.fine_y < 7)
			ppu->vram_addr.fine_y++;
		else
		{
			ppu->vram_addr.fine_y = 0;

			if (ppu->vram_addr.coarse_y == 29)
			{
				ppu->vram_addr.coarse_y = 0;
				ppu->vram_addr.nametable_y = ~ppu->vram_addr.nametable_y;
			}
			else if (ppu->vram_addr.coarse_y == 31)
				ppu->vram_addr.coarse_y = 0;
			else
				ppu->vram_addr.coarse_y++;
		}
	}
}

void ppu_transfer_address_x(PPU* ppu)
{
	if (ppu->bus->mask.render_background || ppu->bus->mask.render_sprites)
	{
		ppu->vram_addr.nametable_x = ppu->tram_addr.nametable_x;
		ppu->vram_addr.coarse_x = ppu->tram_addr.coarse_x;
	}
}

void ppu_transfer_address_y(PPU* ppu)
{
	if (ppu->bus->mask.render_background || ppu->bus->mask.render_sprites)
	{
		ppu->vram_addr.fine_y = ppu->tram_addr.fine_y;
		ppu->vram_addr.nametable_y = ppu->tram_addr.nametable_y;
		ppu->vram_addr.coarse_y = ppu->tram_addr.coarse_y;
	}
}

void ppu_set_pixel(PPU* ppu, uint16_t x, uint16_t y, uint32_t color)
{
	if (x >= 256 || y >= 240)
		return;
	if (color == 0xFF000000)
		return;
	uint32_t index = y * 256 + x;
	ppu->screen[index] = color;
}

uint32_t ppu_get_color_from_palette_ram(PPU* ppu, uint8_t palette, uint8_t pixel)
{
	uint16_t addr = 0x3F00 + ((uint16_t)palette << 2) + pixel;
	uint16_t val = ppu_bus_read(ppu->bus, addr);
	return palScreen[val & 0x3F];
}

#include <stdio.h>
void ppu_get_palette_table(PPU* ppu, uint8_t palette, uint32_t* data)
{
	if (data == NULL)
	{
		printf("%08u %08u %08u %08u\n",
			ppu_get_color_from_palette_ram(ppu, palette, 0),
			ppu_get_color_from_palette_ram(ppu, palette, 1),
			ppu_get_color_from_palette_ram(ppu, palette, 2),
			ppu_get_color_from_palette_ram(ppu, palette, 3)
		);
	}
	else
	{
		data[0] = ppu_get_color_from_palette_ram(ppu, palette, 0);
		data[1] = ppu_get_color_from_palette_ram(ppu, palette, 1);
		data[2] = ppu_get_color_from_palette_ram(ppu, palette, 2);
		data[3] = ppu_get_color_from_palette_ram(ppu, palette, 3);
	}
}

void ppu_get_pattern_table(PPU* ppu, uint8_t i, uint8_t palette, uint32_t* data)
{
	for (uint16_t nTileY = 0; nTileY < 16; nTileY++)
	{
		for (uint16_t nTileX = 0; nTileX < 16; nTileX++)
		{
			// Convert the 2D tile coordinate into a 1D offset into the pattern
			// table memory.
			uint16_t nOffset = nTileY * 256 + nTileX * 16;

			// Now loop through 8 rows of 8 pixels
			for (uint16_t row = 0; row < 8; row++)
			{
				// For each row, we need to read both bit planes of the character
				// in order to extract the least significant and most significant 
				// bits of the 2 bit pixel value. in the CHR ROM, each character
				// is stored as 64 bits of lsb, followed by 64 bits of msb. This
				// conveniently means that two corresponding rows are always 8
				// bytes apart in memory.
				uint8_t tile_lsb = ppu_bus_read(ppu->bus, i * 0x1000 + nOffset + row + 0x0000);
				uint8_t tile_msb = ppu_bus_read(ppu->bus, i * 0x1000 + nOffset + row + 0x0008);


				// Now we have a single row of the two bit planes for the character
				// we need to iterate through the 8-bit words, combining them to give
				// us the final pixel index
				for (uint16_t col = 0; col < 8; col++)
				{
					// We can get the index value by simply adding the bits together
					// but we're only interested in the lsb of the row words because...
					uint8_t pixel = (tile_lsb & 0x01) + (tile_msb & 0x01);

					// ...we will shift the row words 1 bit right for each column of
					// the character.
					tile_lsb >>= 1; tile_msb >>= 1;

					// Now we know the location and NES pixel value for a specific location
					// in the pattern table, we can translate that to a screen colour, and an
					// (x,y) location in the sprite
					data[nTileX * 8 + (7 - col) + (nTileY * 8 + row)* 128] = ppu_get_color_from_palette_ram(ppu, palette, pixel);
				}
			}
		}
	}
}
