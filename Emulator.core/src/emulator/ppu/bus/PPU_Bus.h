#ifndef __EMULATOR_PPU_BUS_H__
#define __EMULATOR_PPU_BUS_H__

#include "../../car/core/Cartridge.h"
#include "TblName.h"


typedef struct ppu_bus
{
	Cartridge** car;
	Tbl_Name* tbl_name;
	uint8_t tblPalette[32];
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
} PPU_Bus;

PPU_Bus* ppu_bus_init(Cartridge**car);
void ppu_bus_destroy(PPU_Bus* bus);
uint8_t ppu_bus_read(PPU_Bus* bus, uint16_t addr);
void ppu_bus_write(PPU_Bus* bus, uint16_t addr, uint8_t value);





#endif