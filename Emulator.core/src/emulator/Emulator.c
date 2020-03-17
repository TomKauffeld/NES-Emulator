#include "Emulator.h"

#include <stdlib.h>
#include <string.h>


Emulator* emulator_init(int test)
{
	Emulator* emulator = (Emulator*)malloc(sizeof(Emulator));
	if (emulator == NULL)
		return NULL;
	emulator->i = test;
	return emulator;
}


int emulator_destroy(Emulator* emulator)
{
	if (emulator == NULL)
		return 0;
	int i = emulator->i;
	free(emulator);
	return i;
}