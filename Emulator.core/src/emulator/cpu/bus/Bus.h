#ifndef __EMULATOR_CPU_BUS_BUS_H__
#define __EMULATOR_CPU_BUS_BUS_H__
#include "../../ppu/core/PPU.h"
#include "../../car/core/Cartridge.h"
#include <inttypes.h>

typedef struct bus {
	uint8_t* ram;
	PPU* ppu;
	Cartridge* car;
} Bus;

Bus* bus_init();

uint8_t bus_read(const Bus* bus, uint16_t addr);

void bus_write(const Bus* bus, uint16_t addr, uint8_t value);

Cartridge* bus_destroy(Bus* bus);

Cartridge* bus_insert_cartridge(Bus* bus, Cartridge* car);

Cartridge* bus_remove_cartridge(Bus* bus);

void bus_tick(Bus* bus);

#endif
