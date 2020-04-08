#ifndef __EMULATOR_EMULATOR_H__
#define __EMULATOR_EMULATOR_H__
#include "cpu/core/CPU.h"


struct emulator
{
	CPU* cpu;
	uint8_t cpu_timer;
};



#include <emulator/emulator.h>
#endif