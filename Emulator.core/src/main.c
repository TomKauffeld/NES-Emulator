#include "emulator/cpu/core/CPU.h"

int main(int argv, char** args)
{
	CPU* cpu = cpu_init();
	
	cpu_destroy(cpu);
	return cpu != NULL ? 0 : 1;
}