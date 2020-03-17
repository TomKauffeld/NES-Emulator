#include <emulator/emulator.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_NUMBER 20

int main(int argc, char ** argv)
{
	Emulator* emulator = emulator_init(TEST_NUMBER);
	int result = emulator_destroy(emulator);
	printf("test : %d", result);

	if (TEST_NUMBER == result)
		return 0;
	return 1;
}