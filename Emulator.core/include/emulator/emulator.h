#ifndef __EMULATOR_H__
#define __EMULATOR_H__

#include "emulator_core.h"
#include <inttypes.h>

typedef struct cartridge Cartridge;
typedef struct emulator Emulator;



EMULATOR_API Emulator* emulator_init();


EMULATOR_API void emulator_destroy(Emulator* emulator);

EMULATOR_API Cartridge* emulator_insert_cartridge(Emulator* emulator, Cartridge* car);

EMULATOR_API Cartridge* emulator_remove_cartridge(Emulator* emulator);

EMULATOR_API void emulator_signal_reset(Emulator* emulator);

EMULATOR_API void emulator_tick(Emulator* emulator);

EMULATOR_API uint8_t emulator_get_cpu_bus(Emulator* emulator, uint16_t addr);

EMULATOR_API uint8_t emulator_get_ppu_bus(Emulator* emulator, uint16_t addr);

EMULATOR_API uint16_t emulator_get_pc(Emulator* emulator);

EMULATOR_API uint8_t emulator_get_cpu_reg_a(Emulator* emulator);

EMULATOR_API uint8_t emulator_get_cpu_reg_x(Emulator* emulator);

EMULATOR_API uint8_t emulator_get_cpu_reg_y(Emulator* emulator);

EMULATOR_API uint8_t emulator_get_cpu_reg_sp(Emulator* emulator);

EMULATOR_API void emulator_set_pc(Emulator* emulator, uint16_t pc);

#endif