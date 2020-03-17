#ifndef __EMULATOR_CPU_REGISTRY_H__
#define __EMULATOR_CPU_REGISTRY_H__

#include <inttypes.h>
#include "Flags.h"

typedef struct registery
{
	uint8_t  a;  // accumulator
	uint8_t  x;  // x register
	uint8_t  y;  // y register
	flags    s;  // status register
	uint8_t  sp; // stack pointer
	uint16_t pc; // program counter
} Registery;


Registery* registery_init();

void registery_destroy(Registery* registery);

void status_set(Registery* registery, flag flag, bool value);

bool status_get(const Registery* registery, flag flag);

#endif