#include "Registery.h"

#include <stdlib.h>
#include <string.h>

Registery* registery_init()
{
	Registery* registery = (Registery*)malloc(sizeof(Registery));
	if (registery == NULL)
		return NULL;

	memset(registery, 0x00, sizeof(Registery));

	return registery;
}

void registery_destroy(Registery* registery)
{
	if (registery == NULL)
		return;
	free(registery);
}

void status_set(Registery* registery, flag flag, bool value)
{
	flag_write(&(registery->s), flag, value);
}

bool status_get(const Registery* registery, flag flag)
{
	return flag_read(registery->s, flag);
}