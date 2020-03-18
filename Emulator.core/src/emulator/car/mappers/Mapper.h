#ifndef __EMULATOR_CAR_MAPPERS_MAPPER_H__
#define __EMULATOR_CAR_MAPPERS_MAPPER_H__
#include <utils/boolean.h>
#include <inttypes.h>


typedef Mapper;

typedef uint32_t(*car_mapper_map)(Mapper * mapper, uint16_t address);
typedef bool(*car_mapper_init)(Mapper * mapper);
typedef void(*car_mapper_destroy)(Mapper* mapper);

typedef struct mapper {
	uint16_t type;
	uint8_t prg_banks;
	uint8_t chr_banks;
	car_mapper_init init;
	car_mapper_destroy destroy;
	car_mapper_map prg_read;
	car_mapper_map prg_write;
	car_mapper_map chr_read;
	car_mapper_map chr_write;
} Mapper;




#endif