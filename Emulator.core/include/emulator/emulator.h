#ifndef __EMULATOR_H__
#define __EMULATOR_H__

#include "emulator_core.h"
#include <utils/boolean.h>
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

EMULATOR_API void emulator_get_screen(Emulator* emulator, uint32_t* screen, size_t size);

EMULATOR_API uint8_t emulator_get_screen_pixel(Emulator* emulator, int x, int y);

EMULATOR_API bool emulator_is_screen_ready(Emulator* emulator);

EMULATOR_API void emulator_get_pattern_table(Emulator* emulator, uint8_t i, uint8_t palette, uint32_t* data);

EMULATOR_API void emulator_get_palette_table(Emulator* emulator, uint8_t palette, uint32_t* data);

#endif