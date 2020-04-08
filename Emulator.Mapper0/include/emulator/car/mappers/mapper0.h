#ifndef __DLL_MAPPER0__
#define __DLL_MAPPER0__

#ifndef EMULATOR_MAPPER0_API
#ifdef EMULATORMAPPER0_EXPORTS
#define EMULATOR_MAPPER0_API __declspec(dllexport)
#else
#define EMULATOR_MAPPER0_API __declspec(dllimport)
#endif
#endif

#include <emulator/car/mappers/mapperProvider.h>

EMULATOR_MAPPER0_API Mapper* mapper_0_provider(uint16_t mapper_id);


#endif