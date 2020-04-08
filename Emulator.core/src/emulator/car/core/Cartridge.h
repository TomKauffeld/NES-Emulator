#ifndef __EMULATOR_CAR_CORE_CARTRIDGE_H__
#define __EMULATOR_CAR_CORE_CARTRIDGE_H__
#include "CartridgeHeader.h"
#include <emulator/car/core/cartridge.h>
#include <emulator/car/mappers/mapperProvider.h>
#include <emulator/car/mappers/mapper.h>
#include <inttypes.h>

#define CARTRIDGE_MIRROR_HORIZONTAL   0x00
#define CARTRIDGE_MIRROR_VERTICAL     0x01
#define CARTRIDGE_MIRROR_ONESCREEN_LO 0x02
#define CARTRIDGE_MIRROR_ONESCREEN_HI 0x03

typedef struct cartridge {
	CartridgeHeader header;
	uint8_t trainer[512];
	uint16_t mapper_id;
	uint8_t* prg;
	uint8_t* chr;
	Mapper* mapper;
	uint8_t mirror;
} Cartridge;




uint8_t cartridge_read_prg(Cartridge* cartridge, uint16_t addr);
void cartridge_write_prg(Cartridge* cartridge, uint16_t addr, uint8_t value);
uint8_t cartridge_read_chr(Cartridge* cartridge, uint16_t addr);
void cartridge_write_chr(Cartridge* cartridge, uint16_t addr, uint8_t value);

#endif