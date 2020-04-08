#include "Mapper0.h"
#include <emulator/car/mappers/mapper.h>
#include <stdlib.h>

Mapper* mapper_0_provider(uint16_t mapper_id)
{
	if (mapper_id != 0)
		return NULL;
	Mapper* mapper = (Mapper*)malloc(sizeof(Mapper));
	if (mapper == NULL)
		return NULL;
	mapper->type = mapper_id;
	mapper->init = &mapper_0_init;
	mapper->destroy = &mapper_0_destroy;
	mapper->prg_read = &mapper_0_prg_read;
	mapper->prg_write = &mapper_0_prg_write;
	mapper->chr_read = &mapper_0_chr_read;
	mapper->chr_write = &mapper_0_chr_write;

	return mapper;
}

bool mapper_0_init(Mapper* mapper)
{
	if (mapper->prg_banks < 1 || mapper->prg_banks > 2)
		return FALSE;
	return TRUE;
}

void mapper_0_destroy(Mapper* mapper)
{
}

uint32_t mapper_0_prg_read(Mapper* mapper, uint16_t addr)
{
	if (mapper->prg_banks == 2 || addr < PRG_BANK_SIZE)
		return addr;
	return addr - PRG_BANK_SIZE;
}

uint32_t mapper_0_prg_write(Mapper* mapper, uint16_t addr)
{
	if (mapper->prg_banks == 2 || addr < PRG_BANK_SIZE)
		return addr;
	return addr - PRG_BANK_SIZE;
}

uint32_t mapper_0_chr_read(Mapper* mapper, uint16_t addr)
{
	return UINT32_MAX;
}

uint32_t mapper_0_chr_write(Mapper* mapper, uint16_t addr)
{
	return addr;
}
