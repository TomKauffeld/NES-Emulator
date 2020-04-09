#ifndef __EMULATOR_PPU_BUS_TBL_NAME_H__
#define __EMULATOR_PPU_BUS_TBL_NAME_H__

#include <inttypes.h>

typedef struct tbl_name
{
	uint8_t * table_1;
	uint8_t * table_2;
}Tbl_Name;

Tbl_Name * tbl_name_init();
void tbl_name_destroy(Tbl_Name* tbl_name);
uint8_t tbl_name_read(Tbl_Name* tbl_name, uint16_t addr, uint8_t mirror);
void tbl_name_write(Tbl_Name* tbl_name, uint16_t addr, uint8_t value, uint8_t mirror);

#endif