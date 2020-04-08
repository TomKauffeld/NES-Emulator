#ifndef __DLL_EMULATOR_MAPPER_DLL_PROVIDER__
#define __DLL_EMULATOR_MAPPER_DLL_PROVIDER__

#ifndef EMULATOR_MAPPER_DLL_PROVIDER_API
#ifdef EMULATORMAPPERPROVIDER_EXPORTS
#define EMULATOR_MAPPER_DLL_PROVIDER_API __declspec(dllexport)
#else
#define EMULATOR_MAPPER_DLL_PROVIDER_API __declspec(dllimport)
#endif
#endif

#include <emulator/car/mappers/mapperProvider.h>

EMULATOR_MAPPER_DLL_PROVIDER_API Mapper* mapper_dll_provider(uint16_t mapper_id);


#endif