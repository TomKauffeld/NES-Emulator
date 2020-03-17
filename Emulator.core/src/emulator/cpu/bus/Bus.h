#ifndef __EMULATOR_CPU_BUS_BUS_H__
#define __EMULATOR_CPU_BUS_BUS_H__

#include <inttypes.h>

typedef struct bus {
	uint8_t* ram;
} Bus;

Bus* bus_init();

uint8_t bus_read(const Bus* bus, uint16_t addr);

void bus_write(const Bus* bus, uint16_t addr, uint8_t value);

void bus_destroy(Bus* bus);


#endif
