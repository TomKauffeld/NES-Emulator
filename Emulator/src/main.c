#include <emulator/emulator.h>
#include <vispa/vispa.h>
#include <stdlib.h>
#include <stdio.h>

#define TEST_NUMBER 20

void on_frame(Vispa* vispa);

int main(int argc, char ** argv)
{
	Emulator* emulator = emulator_init(TEST_NUMBER);
	int result = emulator_destroy(emulator);
	printf("test : %d\n", result);

	if (TEST_NUMBER != result)
		return TEST_NUMBER - result;
	Vispa* vispa = vispa_init(200, 100, "test", &on_frame);
	vispa_tick_automatic(vispa);
	vispa_destroy(vispa);
	return 0;
}

void on_frame(Vispa* vispa)
{

}