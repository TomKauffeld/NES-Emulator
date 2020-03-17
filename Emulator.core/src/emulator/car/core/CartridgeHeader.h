#ifndef __EMULATOR_CAR_CORE_CARTRIDGE_HEADER__H__
#define __EMULATOR_CAR_CORE_CARTRIDGE_HEADER_H__
#include <inttypes.h>

typedef uint8_t cartridge_format;

#define FORMAT_NES_2_0      3
#define FORMAT_INES         2
#define FORMAT_ARCHAIC_INES 1
#define FORMAT_UNKNOWN      0

typedef struct cartridge_header {
	cartridge_format format;
	uint8_t size_prg;
	uint8_t size_chr;
	uint16_t mapper;
} CartridgeHeader;


/*
CartridgeHeader* cartridge_header_init();
void cartridge_header_destroy(CartridgeHeader* cartridgeHeader);

*/



#endif