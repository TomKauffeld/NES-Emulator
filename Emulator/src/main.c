#include <emulator/emulator.h>
#include <emulator/car/core/cartridge.h>
#include <emulator/car/mappers/mapperDllProvider.h>
#include <utils/boolean.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char ** argv)
{
	Emulator* emulator = emulator_init();
	if (emulator == NULL)
		return -1;
	Cartridge* cartridge = cartridge_load_from_file("nestest.nes", &mapper_dll_provider);
	if (cartridge == NULL)
	{
		emulator_destroy(emulator);
		return -2;
	}
	emulator_insert_cartridge(emulator, cartridge);
	emulator_signal_reset(emulator);
	bool running = TRUE;
	emulator_set_pc(emulator, 0xc000);
	uint16_t old_pc = 0;
	int instructions = 8991;
	FILE* f;
	fopen_s(&f, "log.txt", "w");
	if (f == NULL)
		return -3;
	while (is_true(running) && instructions > 0)
	{
		emulator_tick(emulator);
		uint16_t pc = emulator_get_pc(emulator);
		if (pc != old_pc)
		{
			instructions--;
			uint8_t a = emulator_get_cpu_reg_a(emulator);
			uint8_t x = emulator_get_cpu_reg_x(emulator);
			uint8_t y = emulator_get_cpu_reg_y(emulator);
			uint8_t sp = emulator_get_cpu_reg_sp(emulator);

			printf("%04X     A:%02X X:%02X Y:%02X SP:%02X\n", pc, a, x, y, sp);
			fprintf_s(f, "%04X     A:%02X X:%02X Y:%02X SP:%02X\n", pc, a, x, y, sp);
			old_pc = pc;
		}
	}
	fclose(f);
	cartridge_destroy(emulator_remove_cartridge(emulator));
	emulator_destroy(emulator);
	return 0;
}