#include "Flags.h"


bool flag_read(flags flags, flag flag)
{
	return is_true(flags & flag);
}

void flag_write(flags* flags, flag flag, bool value)
{
	if (is_true(value))
		(*flags) |= flag;
	else
		(*flags) &= ~flag;
}


void flag_set_active(flags* flags, flag flag)
{
	flag_write(flags, flag, TRUE);
}

void flag_set_inactive(flags* flags, flag flag)
{

	flag_write(flags, flag, FALSE);
}