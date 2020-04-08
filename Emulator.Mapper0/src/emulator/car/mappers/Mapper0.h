#ifndef __EMULATOR_CAR_MAPPERS_MAPPER_0_H__
#define __EMULATOR_CAR_MAPPERS_MAPPER_0_H__
#include <emulator/car/mappers/mapper0.h>
#include <utils/boolean.h>

bool mapper_0_init(Mapper* mapper);
void mapper_0_destroy(Mapper* mapper);
uint32_t mapper_0_prg_read(Mapper* mapper, uint16_t addr);
uint32_t mapper_0_prg_write(Mapper* mapper, uint16_t addr);
uint32_t mapper_0_chr_read(Mapper* mapper, uint16_t addr);
uint32_t mapper_0_chr_write(Mapper* mapper, uint16_t addr);


#endif