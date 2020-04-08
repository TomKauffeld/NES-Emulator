#include "Cartridge.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


Cartridge* cartridge_load_from_file(const char* file, car_mapper_provider provider)
{
	FILE* f;
	errno_t err = fopen_s(&f, file, "rb");
	if (f == NULL || err != 0)
	{
#ifdef _DEBUG
		printf("Error, couldn't open the file : %s\n", file);
#endif
		return NULL;
	}
	Cartridge* cartridge = (Cartridge*)malloc(sizeof(Cartridge));
	if (cartridge == NULL)
	{
#ifdef _DEBUG
		printf("Error, couldn't allocate memory for the cartridge\n");
#endif
		fclose(f);
		return NULL;
	}
	cartridge->mirror = CARTRIDGE_MIRROR_HORIZONTAL;
	fread_s(&(cartridge->header), sizeof(CartridgeHeader), sizeof(uint8_t), 16, f);

	if (cartridge->header.mapper_1 & 0x04)
		fread_s(cartridge->trainer, sizeof(uint8_t) * 512, sizeof(uint8_t), 512, f);
	else
		memset(cartridge->trainer, 0x00, sizeof(uint8_t) * 512);
	cartridge->mapper_id = ((cartridge->header.mapper_2 >> 4) << 4) | (cartridge->header.mapper_1 >> 4);

#ifdef _DEBUG
	printf("PRG : %u  CHR : %u\n", cartridge->header.size_prg_rom, cartridge->header.size_chr_rom);
#endif
	uint8_t nFileType = 1;
	uint16_t size_prg, size_chr;
	switch (nFileType)
	{
	case 1:
		size_prg = cartridge->header.size_prg_rom * PRG_BANK_SIZE;
		size_chr = cartridge->header.size_chr_rom * CHR_BANK_SIZE;
		cartridge->prg = (uint8_t*)malloc(sizeof(uint8_t) * size_prg);
		if (cartridge->prg == NULL)
		{
			free(cartridge);
			fclose(f);
#ifdef _DEBUG
			printf("Error, couldn't allocate memory for the cartridge PGR\n");
#endif
			return NULL;
		}
		cartridge->chr = (uint8_t*)malloc(sizeof(uint8_t) * size_chr);
		if (cartridge->chr == NULL)
		{
			free(cartridge->prg);
			free(cartridge);
			fclose(f);
#ifdef _DEBUG
			printf("Error, couldn't allocate memory for the cartridge CHR\n");
#endif
			return NULL;
		}
		fread_s(cartridge->prg, sizeof(uint8_t) * size_prg, sizeof(uint8_t), size_prg, f);
		fread_s(cartridge->chr, sizeof(uint8_t) * size_chr, sizeof(uint8_t), size_chr, f);
		break;
	default:
		free(cartridge);
		fclose(f);
#ifdef _DEBUG
		printf("Error, incorrect file type : %u\n", nFileType);
#endif
		return NULL;
	}
	fclose(f);
	cartridge->mapper = (*provider)(cartridge->mapper_id);
	if (cartridge->mapper != NULL)
	{
		cartridge->mapper->chr_banks = cartridge->header.size_chr_rom;
		cartridge->mapper->prg_banks = cartridge->header.size_prg_rom;
		if (is_false((*cartridge->mapper->init)(cartridge->mapper)))
		{
#ifdef _DEBUG
			printf("Error, couldn't initialize mapper %u\n", cartridge->mapper_id);
#endif
			free(cartridge->mapper);
			cartridge->mapper = NULL;
		}
	}
	if (cartridge->mapper == NULL)
	{
#ifdef _DEBUG
		printf("Error, couldn't load mapper %u\n", cartridge->mapper_id);
#endif
		free(cartridge->chr);
		free(cartridge->prg);
		free(cartridge);
		return NULL;
	}
	return cartridge;
}

void cartridge_destroy(Cartridge* cartridge)
{
	if (cartridge == NULL)
		return;
	if (cartridge->mapper != NULL)
	{
		(*cartridge->mapper->destroy)(cartridge->mapper);
		free(cartridge->mapper);
	}
	free(cartridge->chr);
	free(cartridge->prg);
	cartridge->mapper = NULL;
	cartridge->chr = NULL;
	cartridge->prg = NULL;
	free(cartridge);
}

uint8_t cartridge_read_prg(Cartridge* cartridge, uint16_t addr)
{
	uint32_t realAddr = (*cartridge->mapper->prg_read)(cartridge->mapper, addr);
	if (realAddr < UINT32_MAX)
		return cartridge->prg[realAddr];
	return 0x00;
}

void cartridge_write_prg(Cartridge* cartridge, uint16_t addr, uint8_t value)
{
	uint32_t realAddr = (*cartridge->mapper->prg_write)(cartridge->mapper, addr);
	if (realAddr < UINT32_MAX)
		cartridge->prg[realAddr] = value;
}

uint8_t cartridge_read_chr(Cartridge* cartridge, uint16_t addr)
{
	uint32_t realAddr = (*cartridge->mapper->chr_read)(cartridge->mapper, addr);
	if (realAddr < UINT32_MAX)
		return cartridge->chr[realAddr];
	return 0x00;
}

void cartridge_write_chr(Cartridge* cartridge, uint16_t addr, uint8_t value)
{
	uint32_t realAddr = (*cartridge->mapper->chr_write)(cartridge->mapper, addr);
	if (realAddr < UINT32_MAX)
		cartridge->chr[realAddr] = value;
}