#ifndef __EMULATOR_CAR_CORE_CARTRIDGE_H__
#define __EMULATOR_CAR_CORE_CARTRIDGE_H__
#include "CartridgeHeader.h"
#include <inttypes.h>

typedef struct cartridge {
	CartridgeHeader* header;
	//trainer
	uint8_t* prg;
	uint8_t* chr;
} Cartridge;

Cartridge* cartridge_load_from_memory(const uint8_t* rom, size_t rom_size);

Cartridge* cartridge_load_from_file(const char* file);

void cartridge_destroy(Cartridge* cartridge);


#endif