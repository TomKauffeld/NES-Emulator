#ifndef __DLL_EMULATOR_CAR_MAPPERS_MAPPER_PROVIDER_H__
#define __DLL_EMULATOR_CAR_MAPPERS_MAPPER_PROVIDER_H__

#include <emulator/emulator_core.h>
#include <inttypes.h>

typedef struct mapper Mapper;

typedef Mapper* (*car_mapper_provider)(uint16_t mapper_id);

#endif