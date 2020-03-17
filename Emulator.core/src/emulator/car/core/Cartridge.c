#include "Cartridge.h"
#include <stdlib.h>
#include <string.h>

uint8_t nes[4] = { 0x4e, 0x45, 0x53, 0x1a };

Cartridge* cartridge_init(uint8_t prg_size, uint8_t chr_size)
{
	size_t prg = ((size_t)prg_size) * 16 * 1024;
	size_t chr = ((size_t)chr_size) *  8 * 1024;
	Cartridge* cartridge = (Cartridge*)malloc(sizeof(Cartridge));
	if (cartridge == NULL)
		return NULL;

	memset(cartridge, 0x00, sizeof(Cartridge));
	
	//cartridge->header = cartridge_header_init();
	if (cartridge->header == NULL)
	{
		free(cartridge);
		return NULL;
	}
	cartridge->prg = (uint8_t*)malloc(prg * sizeof(uint8_t));
	if (cartridge->prg == NULL)
	{
		//cartridge_header_destroy(cartridge->header);
		free(cartridge);
		return NULL;
	}
	if (chr > 0)
	{
		cartridge->chr = (uint8_t*)malloc(chr * sizeof(uint8_t));
		if (cartridge->chr == NULL)
		{
			//cartridge_header_destroy(cartridge->header);
			free(cartridge->prg);
			free(cartridge);
			return NULL;
		}
		memset(cartridge->chr, 0x00, chr * sizeof(uint8_t));
	}

	memset(cartridge->prg, 0x00, prg * sizeof(uint8_t));

	cartridge->header->size_chr = chr_size;
	cartridge->header->size_prg = prg_size;

	return cartridge;
}

void cartridge_destroy(Cartridge* cartridge)
{
	if (cartridge == NULL)
		return;
	//cartridge_header_destroy(cartridge->header);
	free(cartridge->prg);
	if (cartridge->chr != NULL)
		free(cartridge->chr);
	free(cartridge);
}

Cartridge* cartridge_load_from_memory(const uint8_t* rom, size_t rom_size)
{
	if (rom_size < 16)
		return NULL;
	if (memcmp(rom, nes, sizeof(uint8_t) * 4) != 0)
		return NULL;
	Cartridge* cartridge = cartridge_init(rom[4], rom[5]);
	if (cartridge == NULL)
		return NULL;
	if ((rom[7] & 0x0c) == 0x08)
		cartridge->header->format = FORMAT_NES_2_0;
	else if ((rom[7] & 0x0c) == 0x00 && rom[12] == 0 && rom[13] == 0 && rom[14] == 0 && rom[15] == 0)
		cartridge->header->format = FORMAT_INES;
	else
		cartridge->header->format = FORMAT_ARCHAIC_INES;
	return NULL;
}