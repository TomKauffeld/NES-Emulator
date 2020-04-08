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
