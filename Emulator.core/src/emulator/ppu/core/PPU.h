#ifndef __EMULATOR_PPU_CORE_PPU_H__
#define __EMULATOR_PPU_CORE_PPU_H__
#include <inttypes.h>
#include "../../car/core/Cartridge.h"


typedef union loopy_register_u
{
	// Source OneLoneCoder
	// Credit to Loopy for working this out
	struct
	{
		uint16_t coarse_x : 5;
		uint16_t coarse_y : 5;
		uint16_t nametable_x : 1;
		uint16_t nametable_y : 1;
		uint16_t fine_y : 3;
		uint16_t unused : 1;
	};
	uint16_t reg;
} loopy_register;


typedef struct ppu {
	Cartridge ** car;
	uint8_t tblName[2][1024];
	uint8_t tblPattern[2][4096];
	uint8_t tblPalette[32];
	int16_t scanline;
	int16_t cycle;
	bool frame;
	union status_u
	{
		struct {
			uint8_t unused : 5;
			uint8_t sprite_overflow : 1;
			uint8_t sprite_zero_hit : 1;
			uint8_t vertical_blank : 1;
		};
		uint8_t reg;
	} status;
	union mask_u
	{
		struct
		{
			uint8_t grayscale : 1;
			uint8_t render_background_left : 1;
			uint8_t render_sprites_left : 1;
			uint8_t render_background : 1;
			uint8_t render_sprites : 1;
			uint8_t enhance_red : 1;
			uint8_t enhance_green : 1;
			uint8_t enhance_blue : 1;
		};
		uint8_t reg;
	} mask;	
	union PPUCTRL
	{
		struct
		{
			uint8_t nametable_x : 1;
			uint8_t nametable_y : 1;
			uint8_t increment_mode : 1;
			uint8_t pattern_sprite : 1;
			uint8_t pattern_background : 1;
			uint8_t sprite_size : 1;
			uint8_t slave_mode : 1; // unused
			uint8_t enable_nmi : 1;
		};
		uint8_t reg;
	} control;
	loopy_register vram_addr;
	loopy_register tram_addr; 
	uint8_t fine_x;
	uint8_t address_latch;
	uint8_t ppu_data_buffer;
	uint8_t bg_next_tile_id;
	uint8_t bg_next_tile_attrib;
	uint8_t bg_next_tile_lsb;
	uint8_t bg_next_tile_msb;
	uint16_t bg_shifter_pattern_lo;
	uint16_t bg_shifter_pattern_hi;
	uint16_t bg_shifter_attrib_lo;
	uint16_t bg_shifter_attrib_hi;
	bool nmi;
	uint32_t* screen;
} PPU;

PPU* ppu_init(Cartridge** car);

void ppu_destroy(PPU* ppu);

uint8_t ppu_read(PPU* ppu, uint16_t addr);

void ppu_write(PPU* ppu, uint16_t addr, uint8_t value);

uint8_t ppu_bus_read(PPU* ppu, uint16_t addr);

void ppu_bus_write(PPU* ppu, uint16_t addr, uint8_t value);

void ppu_tick(PPU* ppu);

void ppu_update_shifters(PPU* ppu);

void ppu_load_background_shifters(PPU* ppu);

void ppu_increment_scroll_x(PPU* ppu);

void ppu_increment_scroll_y(PPU* ppu);

void ppu_transfer_address_x(PPU* ppu);

void ppu_transfer_address_y(PPU* ppu);

void ppu_set_pixel(PPU* ppu, uint16_t x, uint16_t y, uint32_t color);

uint32_t ppu_get_color_from_palette_ram(PPU* ppu, uint8_t palette, uint8_t pixel);

#endif