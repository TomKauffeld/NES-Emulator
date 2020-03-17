#ifndef __EMULATOR_CPU_CORE_FLAGS__
#define __EMULATOR_CPU_CORE_FLAGS__

#include <inttypes.h>
#include "../../../utils/boolean.h"


typedef uint8_t flag;
typedef uint8_t flags;

#define FLAG_C 0x01 // Carry Bit
#define FLAG_Z 0x02 // Zero
#define FLAG_I 0x04 // Disable Interrupts
#define FLAG_D 0x08 // Decimal Mode (unused in this implementation)
#define FLAG_B 0x10 // Break
#define FLAG_U 0x20 // Unused
#define FLAG_V 0x40 // Overflow
#define FLAG_N 0x80 // Negative



bool flag_read(flags flags, flag flag);

void flag_write(flags* flags, flag flag, bool value);

void flag_set_active(flags* flags, flag flag);

void flag_set_inactive(flags* flags, flag flag);


#endif