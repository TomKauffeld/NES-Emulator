#ifndef __EMULATOR_CAR_CORE_CARTRIDGE_HEADER__H__
#define __EMULATOR_CAR_CORE_CARTRIDGE_HEADER_H__
#include <inttypes.h>


typedef struct cartridge_header {
	char name[4];
	uint8_t size_prg_rom;
	uint8_t size_chr_rom;
	uint8_t mapper_1;
	uint8_t mapper_2;
	uint8_t size_prg_ram;
	uint8_t tv_system_1;
	uint8_t tv_system_2;
	uint8_t unused_1;
	uint8_t unused_2;
	uint8_t unused_3;
	uint8_t unused_4;
	uint8_t unused_5;
} CartridgeHeader;




#endif