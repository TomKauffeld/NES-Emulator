#include "PPU_Bus.h"
#include <stdlib.h>
#include <string.h>

PPU_Bus* ppu_bus_init(Cartridge** car)
{
	PPU_Bus* bus = (PPU_Bus*)malloc(sizeof(PPU_Bus));
	if (bus == NULL)
		return NULL;
	bus->car = car;
	bus->tbl_name = tbl_name_init();
	if (bus->tbl_name == NULL)
	{
		free(bus);
		return NULL;
	}
	memset(bus->tblPalette, 0x00, 32 * sizeof(uint8_t));
	return bus;
}

void ppu_bus_destroy(PPU_Bus* bus)
{
	if (bus == NULL)
		return;
	tbl_name_destroy(bus->tbl_name);
	free(bus);
}

uint8_t ppu_bus_read(PPU_Bus* bus, uint16_t addr)
{
	addr &= 0x3FFF;
	if (addr >= 0x0000 && addr <= 0x1FFF)
		return cartridge_read_chr(*(bus->car), addr);
	if (addr >= 0x2000 && addr <= 0x3EFF)
		return tbl_name_read(bus->tbl_name, addr, (*bus->car)->mirror);
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
		return bus->tblPalette[addr] &(bus->mask.grayscale ? 0x30 : 0x3F);
	}
	return 0x00;
}

void ppu_bus_write(PPU_Bus* bus, uint16_t addr, uint8_t value)
{
	addr &= 0x3FFF;
	if (addr >= 0x0000 && addr <= 0x1FFF)
		cartridge_write_chr(*(bus->car), addr, value);
	if (addr >= 0x2000 && addr <= 0x3EFF)
		tbl_name_write(bus->tbl_name, addr, value, (*bus->car)->mirror);
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
		bus->tblPalette[addr] = value;
	}
}