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

	ppu->car = car;
	return ppu;
}

void ppu_destroy(PPU* ppu)
{
	if (ppu == NULL)
		return;
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
		ppu->ppu_data_buffer = ppu_bus_read(ppu, ppu->vram_addr.reg);
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
		ppu->mask.reg = value;
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
		ppu_bus_write(ppu, ppu->vram_addr.reg, value);
		ppu->vram_addr.reg += (ppu->control.increment_mode ? 32 : 1);
		break;
	default:
		return;
	}
}

uint8_t ppu_bus_read(PPU* ppu, uint16_t addr)
{
	if (addr >= 0x0000 && addr <= 0x1FFF)
		//return ppu->tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF];
		return cartridge_read_chr(*ppu->car, addr);
	if (addr >= 0x2000 && addr <= 0x3EFF)
	{
		addr &= 0x0FFF;
		if ((*ppu->car)->mirror == CARTRIDGE_MIRROR_VERTICAL)
		{
			if (addr >= 0x0000 && addr <= 0x03FF)
				return ppu->tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				return ppu->tblName[1][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				return ppu->tblName[0][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				return ppu->tblName[1][addr & 0x03FF];
		}
		else if ((*ppu->car)->mirror == CARTRIDGE_MIRROR_HORIZONTAL)
		{
			if (addr >= 0x0000 && addr <= 0x03FF)
				return ppu->tblName[0][addr & 0x03FF];
			if (addr >= 0x0400 && addr <= 0x07FF)
				return ppu->tblName[0][addr & 0x03FF];
			if (addr >= 0x0800 && addr <= 0x0BFF)
				return ppu->tblName[1][addr & 0x03FF];
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				return ppu->tblName[1][addr & 0x03FF];
		}
	}
	if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr &= 0x001F;
		if (addr == 0x0010) 
			addr = 0x0000;
		if (addr == 0x0014)
			addr = 0x0004;
		if (addr == 0x0018)
			addr = 0x0008;
		if (addr == 0x001C)
			addr = 0x000C;
		return ppu->tblPalette[addr] & (ppu->mask.grayscale ? 0x30 : 0x3F);
	}
	return 0x00;
}

void ppu_bus_write(PPU* ppu, uint16_t addr, uint8_t value)
{
	
	if (addr >= 0x0000 && addr <= 0x1FFF)
		//ppu->tblPattern[(addr & 0x1000) >> 12][addr & 0x0FFF] = value;
		cartridge_write_chr(*ppu->car, addr, value);
	if (addr >= 0x2000 && addr <= 0x3EFF)
	{
		addr &= 0x0FFF;
		if ((*ppu->car)->mirror == CARTRIDGE_MIRROR_VERTICAL)
		{
			// Vertical
			if (addr >= 0x0000 && addr <= 0x03FF)
				ppu->tblName[0][addr & 0x03FF] = value;
			if (addr >= 0x0400 && addr <= 0x07FF)
				ppu->tblName[1][addr & 0x03FF] = value;
			if (addr >= 0x0800 && addr <= 0x0BFF)
				ppu->tblName[0][addr & 0x03FF] = value;
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				ppu->tblName[1][addr & 0x03FF] = value;
		}
		else if ((*ppu->car)->mirror == CARTRIDGE_MIRROR_HORIZONTAL)
		{
			// Horizontal
			if (addr >= 0x0000 && addr <= 0x03FF)
				ppu->tblName[0][addr & 0x03FF] = value;
			if (addr >= 0x0400 && addr <= 0x07FF)
				ppu->tblName[0][addr & 0x03FF] = value;
			if (addr >= 0x0800 && addr <= 0x0BFF)
				ppu->tblName[1][addr & 0x03FF] = value;
			if (addr >= 0x0C00 && addr <= 0x0FFF)
				ppu->tblName[1][addr & 0x03FF] = value;
		}
	}
	if (addr >= 0x3F00 && addr <= 0x3FFF)
	{
		addr &= 0x001F;
		if (addr == 0x0010) 
			addr = 0x0000;
		if (addr == 0x0014)
			addr = 0x0004;
		if (addr == 0x0018)
			addr = 0x0008;
		if (addr == 0x001C)
			addr = 0x000C;
		ppu->tblPalette[addr] = value;
	}
}

void ppu_tick(PPU * ppu)
{
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
				ppu->bg_next_tile_id = ppu_bus_read(ppu, 0x2000 | (ppu->vram_addr.reg & 0x0FFF));
				break; 
			case 2:
				ppu->bg_next_tile_attrib = ppu_bus_read(ppu, 
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
				ppu->bg_next_tile_lsb = ppu_bus_read(ppu, (ppu->control.pattern_background << 12) + ((uint16_t)ppu->bg_next_tile_id << 4) + (ppu->vram_addr.fine_y) + 0);

				break;
			case 6:
				ppu->bg_next_tile_msb = ppu_bus_read(ppu, (ppu->control.pattern_background << 12) + ((uint16_t)ppu->bg_next_tile_id << 4) + (ppu->vram_addr.fine_y) + 8);
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
			ppu->bg_next_tile_id = ppu_bus_read(ppu, 0x2000 | (ppu->vram_addr.reg & 0x0FFF));
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
	if (ppu->mask.render_background)
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
	if (ppu->mask.render_background)
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
	if (ppu->mask.render_background || ppu->mask.render_sprites)
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
	if (ppu->mask.render_background || ppu->mask.render_sprites)
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
	if (ppu->mask.render_background || ppu->mask.render_sprites)
	{
		ppu->vram_addr.nametable_x = ppu->tram_addr.nametable_x;
		ppu->vram_addr.coarse_x = ppu->tram_addr.coarse_x;
	}
}

void ppu_transfer_address_y(PPU* ppu)
{
	if (ppu->mask.render_background || ppu->mask.render_sprites)
	{
		ppu->vram_addr.fine_y = ppu->tram_addr.fine_y;
		ppu->vram_addr.nametable_y = ppu->tram_addr.nametable_y;
		ppu->vram_addr.coarse_y = ppu->tram_addr.coarse_y;
	}
}

void ppu_set_pixel(PPU* ppu, uint16_t x, uint16_t y, uint16_t color)
{
	if (x >= 256 || y >= 240)
		return;
	uint32_t index = y * 256 + x;
	ppu->screen[index] = color;
}

uint32_t ppu_get_color_from_palette_ram(PPU* ppu, uint8_t palette, uint8_t pixel)
{
	uint16_t val = ppu_bus_read(ppu, 0x3F00 + (palette << 2) + pixel);
	return palScreen[val & 0x3F];
}
