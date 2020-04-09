#include "Bus.h"
#include <stdlib.h>
#include <string.h>
#include "../core/settings.h"

Bus* bus_init()
{
	Bus* bus = (Bus*)malloc(sizeof(Bus));
	if (bus == NULL)
		return NULL;
	
	memset(bus, 0x00, sizeof(Bus));

	size_t ram_size = RAM_END - RAM_START + 1;

	bus->ram = (uint8_t*)malloc(sizeof(uint8_t) * ram_size);
	if (bus->ram == NULL)
	{
		free(bus);
		return NULL;
	}
	memset(bus->ram, 0x00, sizeof(uint8_t)* ram_size);
	bus->car = NULL;
	bus->ppu = ppu_init(&(bus->car));
	if (bus->ppu == NULL)
	{
		free(bus->ram);
		free(bus);
		return NULL;
	}
	return bus;
}

uint8_t bus_read(const Bus* bus, uint16_t addr)
{
	if (addr >= RAM_START && addr <= RAM_END)
		return bus->ram[addr - RAM_START];
	if (addr >= RAM_CLONE_START && addr <= RAM_CLONE_END)
		return bus_read(bus, (addr & (RAM_END - RAM_START)) + RAM_START);
	if (addr >= PPU_START && addr <= PPU_END)
		return ppu_read(bus->ppu, addr - PPU_START);
	if (addr >= PPU_CLONE_START && addr <= PPU_CLONE_END)
		return bus_read(bus, (addr % (PPU_END - PPU_START )) + PPU_START);
	if (addr >= CAR_PRG_START && addr <= CAR_PRG_END)
		return cartridge_read_prg(bus->car, addr - CAR_PRG_START);
	return 0x00;
}

void bus_write(const Bus* bus, uint16_t addr, uint8_t value)
{
	if (addr >= RAM_START && addr <= RAM_END)
		bus->ram[addr - RAM_START] = value;
	else if (addr >= RAM_CLONE_START && addr <= RAM_CLONE_END)
		bus_write(bus, (addr & (RAM_END - RAM_START)) + RAM_START, value);
	else if (addr >= PPU_START && addr <= PPU_END)
		ppu_write(bus->ppu, addr - PPU_START, value);
	else if (addr >= PPU_CLONE_START && addr <= PPU_CLONE_END)
		bus_write(bus, (addr % (PPU_END - PPU_START)) + PPU_START, value);
	else if (addr >= CAR_PRG_START && addr <= CAR_PRG_END)
		cartridge_write_prg(bus->car, addr - CAR_PRG_START, value);
}

Cartridge* bus_destroy(Bus* bus)
{
	if (bus == NULL)
		return;
	Cartridge* car = bus->car;
	bus->car = NULL;
	free(bus->ram);
	free(bus);
	return car;
}

Cartridge* bus_insert_cartridge(Bus* bus, Cartridge* car)
{
	Cartridge* old = bus->car;
	bus->car = car;
	return old;
}

Cartridge* bus_remove_cartridge(Bus* bus)
{
	Cartridge* old = bus->car;
	bus->car = NULL;
	return old;
}

void bus_tick(Bus* bus)
{
	ppu_tick(bus->ppu);
}
