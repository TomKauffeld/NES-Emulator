#include "Emulator.h"

#include <stdlib.h>
#include <string.h>


Emulator* emulator_init()
{
	Emulator* emulator = (Emulator*)malloc(sizeof(Emulator));
	if (emulator == NULL)
		return NULL;
	emulator->cpu_timer = 0;
	emulator->cpu = cpu_init();
	if (emulator->cpu == NULL)
	{
		free(emulator);
		return NULL;
	}
	return emulator;
}

void emulator_destroy(Emulator* emulator)
{
	if (emulator == NULL)
		return;
	cpu_destroy(emulator->cpu);
	free(emulator);
}

Cartridge* emulator_insert_cartridge(Emulator* emulator, Cartridge* car)
{
	return bus_insert_cartridge(emulator->cpu->bus, car);
}

Cartridge* emulator_remove_cartridge(Emulator* emulator)
{
	return bus_remove_cartridge(emulator->cpu->bus);
}

void emulator_signal_reset(Emulator* emulator)
{
	cpu_signal_reset(emulator->cpu);
}

void emulator_tick(Emulator* emulator)
{
	emulator->cpu_timer++;
	bus_tick(emulator->cpu->bus);
	if (emulator->cpu_timer > 3)
	{
		cpu_clock(emulator->cpu);
		emulator->cpu_timer = 0;
	}
}

uint8_t emulator_get_cpu_bus(Emulator* emulator, uint16_t addr)
{
	return cpu_bus_read(emulator->cpu, addr);
}

uint8_t emulator_get_ppu_bus(Emulator* emulator, uint16_t addr)
{
	return ppu_bus_read(emulator->cpu->bus->ppu, addr);
}

uint16_t emulator_get_pc(Emulator* emulator)
{
	return emulator->cpu->registery->pc;
}

uint8_t emulator_get_cpu_reg_a(Emulator* emulator)
{
	return emulator->cpu->registery->a;
}

uint8_t emulator_get_cpu_reg_x(Emulator* emulator)
{
	return emulator->cpu->registery->x;
}

uint8_t emulator_get_cpu_reg_y(Emulator* emulator)
{
	return emulator->cpu->registery->y;
}

uint8_t emulator_get_cpu_reg_sp(Emulator* emulator)
{
	return emulator->cpu->registery->sp;
}

void emulator_set_pc(Emulator* emulator, uint16_t pc)
{
	emulator->cpu->registery->pc = pc;
}

void emulator_get_screen(Emulator* emulator, uint32_t* screen, size_t size)
{
	memcpy_s(screen, size * sizeof(uint32_t), emulator->cpu->bus->ppu->screen, sizeof(uint32_t) * 256 * 240);
}

uint8_t emulator_get_screen_pixel(Emulator* emulator, int x, int y)
{
	if (x >= 256 || y >= 240)
		return;
	uint32_t index = y * 256 + x;
	return emulator->cpu->bus->ppu->screen[index];
}

bool emulator_is_screen_ready(Emulator* emulator)
{
	return emulator->cpu->bus->ppu->frame;
}

void emulator_get_pattern_table(Emulator* emulator, uint8_t i, uint8_t palette, uint32_t* data)
{
	ppu_get_pattern_table(emulator->cpu->bus->ppu, i, palette, data);
}

void emulator_get_palette_table(Emulator* emulator, uint8_t palette, uint32_t* data)
{
	ppu_get_palette_table(emulator->cpu->bus->ppu, palette, data);
}
