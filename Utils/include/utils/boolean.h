#ifndef __UTILS_CORE_BOOLEAN_H__
#define __UTILS_CORE_BOOLEAN_H__
#include <inttypes.h>
#include "utils.h"


#ifndef bool
typedef uint8_t bool;
#endif

#define TRUE  0x01
#define FALSE 0x00

UTILS_API bool is_true(bool b);

UTILS_API bool is_false(bool b);

#endif
