#include "TblName.h"
#include <stdlib.h>
#include "../../car/core/Cartridge.h"

Tbl_Name* tbl_name_init()
{
	Tbl_Name* tbl_name = (Tbl_Name*)malloc(sizeof(Tbl_Name));
	if (tbl_name == NULL)
		return NULL;
	tbl_name->table_1 = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
	if (tbl_name->table_1 == NULL)
	{
		free(tbl_name);
		return NULL;
	}
	tbl_name->table_2 = (uint8_t*)malloc(sizeof(uint8_t) * 1024);
	if (tbl_name->table_2 == NULL)
	{
		free(tbl_name->table_1);
		free(tbl_name);
		return NULL;
	}
	return tbl_name;
}

void tbl_name_destroy(Tbl_Name* tbl_name)
{
	if (tbl_name == NULL)
		return;
	free(tbl_name->table_1);
	free(tbl_name->table_2);
	free(tbl_name);
}

uint8_t tbl_name_read(Tbl_Name* tbl_name, uint16_t addr, uint8_t mirror)
{
	addr &= 0x0FFF;
	if (mirror == CARTRIDGE_MIRROR_VERTICAL)
	{
		if (addr >= 0x0000 && addr <= 0x03FF)
			return tbl_name->table_1[addr & 0x03FF];
		if (addr >= 0x0400 && addr <= 0x07FF)
			return tbl_name->table_2[addr & 0x03FF];
		if (addr >= 0x0800 && addr <= 0x0BFF)
			return tbl_name->table_1[addr & 0x03FF];
		if (addr >= 0x0C00 && addr <= 0x0FFF)
			return tbl_name->table_2[addr & 0x03FF];
	}
	else if (mirror == CARTRIDGE_MIRROR_HORIZONTAL)
	{
		if (addr >= 0x0000 && addr <= 0x03FF)
			return tbl_name->table_1[addr & 0x03FF];
		if (addr >= 0x0400 && addr <= 0x07FF)
			return tbl_name->table_1[addr & 0x03FF];
		if (addr >= 0x0800 && addr <= 0x0BFF)
			return tbl_name->table_2[addr & 0x03FF];
		if (addr >= 0x0C00 && addr <= 0x0FFF)
			return tbl_name->table_2[addr & 0x03FF];
	}
}

void tbl_name_write(Tbl_Name* tbl_name, uint16_t addr, uint8_t value, uint8_t mirror)
{
	addr &= 0x0FFF;
	if (mirror == CARTRIDGE_MIRROR_VERTICAL)
	{
		if (addr >= 0x0000 && addr <= 0x03FF)
			tbl_name->table_1[addr & 0x03FF] = value;
		if (addr >= 0x0400 && addr <= 0x07FF)
			tbl_name->table_2[addr & 0x03FF] = value;
		if (addr >= 0x0800 && addr <= 0x0BFF)
			tbl_name->table_1[addr & 0x03FF] = value;
		if (addr >= 0x0C00 && addr <= 0x0FFF)
			tbl_name->table_2[addr & 0x03FF] = value;
	}
	else if (mirror == CARTRIDGE_MIRROR_HORIZONTAL)
	{
		if (addr >= 0x0000 && addr <= 0x03FF)
			tbl_name->table_1[addr & 0x03FF] = value;
		if (addr >= 0x0400 && addr <= 0x07FF)
			tbl_name->table_1[addr & 0x03FF] = value;
		if (addr >= 0x0800 && addr <= 0x0BFF)
			tbl_name->table_2[addr & 0x03FF] = value;
		if (addr >= 0x0C00 && addr <= 0x0FFF)
			tbl_name->table_2[addr & 0x03FF] = value;
	}
}
