#include "Boolean.h"

bool is_true(bool b) {
	return b != FALSE;
}

bool is_false(bool b) {
	return !is_true(b);
}