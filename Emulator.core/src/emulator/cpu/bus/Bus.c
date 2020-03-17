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

	memset(bus->ram, 0x00, sizeof(uint8_t) * ram_size);

	return bus;
}

uint8_t bus_read(const Bus* bus, uint16_t addr)
{
	if (addr >= RAM_START && addr <= RAM_END)
		return bus->ram[addr - RAM_START];
	if (addr >= RAM_CLONE_START && addr <= RAM_CLONE_END)
		return bus_read(bus, (addr & (RAM_CLONE_END - RAM_CLONE_START + 1)) + RAM_START);
	return 0x00;
}

void bus_write(const Bus* bus, uint16_t addr, uint8_t value)
{
	if (addr >= RAM_START && addr <= RAM_END)
		bus->ram[addr - RAM_START] = value;
	else if (addr >= RAM_CLONE_START && addr <= RAM_CLONE_END)
		bus_write(bus, (addr & (RAM_CLONE_END - RAM_CLONE_START + 1)) + RAM_START, value);
}

void bus_destroy(Bus* bus)
{
	if (bus == NULL)
		return;
	free(bus->ram);
	free(bus);
}