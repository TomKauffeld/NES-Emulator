#ifndef __DLL_EMULATOR_CAR_MAPPERS_MAPPER_H__
#define __DLL_EMULATOR_CAR_MAPPERS_MAPPER_H__

#include <emulator/emulator_core.h>
#include <utils/boolean.h>
#include <inttypes.h>

#define PRG_BANK_SIZE 16384
#define CHR_BANK_SIZE 8192

typedef struct mapper Mapper;

typedef bool(*car_mapper_init)(Mapper* mapper);
typedef void(*car_mapper_destroy)(Mapper* mapper);
typedef uint32_t(*car_mapper_map)(Mapper* mapper, uint16_t address);

typedef struct mapper {
	uint16_t type;
	uint8_t prg_banks;
	uint8_t chr_banks;
	void* user_ptr;
	car_mapper_init init;
	car_mapper_destroy destroy;
	car_mapper_map prg_read;
	car_mapper_map prg_write;
	car_mapper_map chr_read;
	car_mapper_map chr_write;
} Mapper;


#endif