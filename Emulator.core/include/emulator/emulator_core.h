#ifndef EMULATOR_API
#ifdef EMULATOR_CORE_DLL
#define EMULATOR_API __declspec(dllexport)
#else
#define EMULATOR_API __declspec(dllimport)
#endif
#endif