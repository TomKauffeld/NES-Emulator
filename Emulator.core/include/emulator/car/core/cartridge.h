#ifndef __DLL_EMULATOR_CAR_CORE_CARTRIDGE_H__
#define __DLL_EMULATOR_CAR_CORE_CARTRIDGE_H__
#include <emulator/emulator_core.h>
#include <emulator/car/mappers/mapperProvider.h>
typedef struct cartridge Cartridge;


EMULATOR_API Cartridge* cartridge_load_from_file(const char* file, car_mapper_provider provider);
EMULATOR_API void cartridge_destroy(Cartridge* cartridge);

#endif