#ifndef __EMULATOR_H__
#define __EMULATOR_H__

#ifdef EMULATOR_CORE_DLL
#define EMULATOR_API __declspec(dllexport)
#else
#define EMULATOR_API __declspec(dllimport)
#endif

struct emulator;
typedef struct emulator Emulator;



EMULATOR_API Emulator* emulator_init(int test);


EMULATOR_API int emulator_destroy(Emulator*);



#endif