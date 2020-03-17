#ifndef __UTILS_BOOLEAN_H__
#define __UTILS_BOOLEAN_H__
#include <inttypes.h>

#ifndef bool
typedef uint8_t bool;
#endif

#define TRUE  0x01
#define FALSE 0x00

bool is_true(bool b);

bool is_false(bool b);

#endif
