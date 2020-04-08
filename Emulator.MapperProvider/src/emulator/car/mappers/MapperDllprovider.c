#include "MapperDllProvider.h"
#include <emulator/car/mappers/mapper0.h>

Mapper* mapper_dll_provider(uint16_t mapper_id)
{
	switch (mapper_id)
	{
	case 0:
		return mapper_0_provider(mapper_id);
	default:
		return NULL;
	}
}