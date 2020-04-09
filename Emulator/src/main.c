#include <emulator/emulator.h>
#include <emulator/car/core/cartridge.h>
#include <emulator/car/mappers/mapperDllProvider.h>
#include <utils/boolean.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#define WIDTH 256
#define HEIGHT 240


int main(int argc, char ** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return -4;
	SDL_Window* window;
	SDL_Renderer* renderer;
	if (SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE, &window, &renderer) != 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Couldn't init screen/renderer");
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
		SDL_Quit();
		return -5;
	}
	Emulator* emulator = emulator_init();
	if (emulator == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't init the emulator");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	Cartridge* cartridge = cartridge_load_from_file("nestest.nes ", &mapper_dll_provider);
	if (cartridge == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load the cartridge");
		emulator_destroy(emulator);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -2;
	}
	emulator_insert_cartridge(emulator, cartridge);
	emulator_signal_reset(emulator);
	bool running = TRUE;
	SDL_Texture* buffer = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STREAMING,
		WIDTH,
		HEIGHT);
	if (buffer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, "Couldn't create the buffer");
		SDL_LogError(SDL_LOG_CATEGORY_VIDEO, SDL_GetError());
		cartridge_destroy(emulator_remove_cartridge(emulator));
		emulator_destroy(emulator);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	uint32_t* pixels = (uint32_t*)malloc(sizeof(uint32_t) * WIDTH * HEIGHT);
	if (pixels == NULL)
	{
		cartridge_destroy(emulator_remove_cartridge(emulator));
		emulator_destroy(emulator);
		SDL_DestroyTexture(buffer);
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}
	int pitch = WIDTH * sizeof(uint32_t);
	while (is_true(running))
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			switch (event.type)
			{
			case SDL_QUIT:
				running = FALSE;
				break;
			default:
				break;
			}
		}
		if (emulator_get_pc(emulator) == 0xC28F)
		{
			int i = 0;
		}
		emulator_tick(emulator);
		if (emulator_is_screen_ready(emulator))
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			emulator_get_screen(emulator, pixels, WIDTH * HEIGHT);
			if (SDL_UpdateTexture(buffer, NULL, pixels, pitch) == 0)
			{
				if (SDL_RenderCopy(renderer, buffer, NULL, NULL) != 0)
				{
					SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't render the buffer");
					SDL_LogError(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
				}
			}
			else
			{
				SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't update the buffer");
				SDL_LogError(SDL_LOG_CATEGORY_RENDER, SDL_GetError());
			}
			SDL_RenderPresent(renderer);
		}
	}



	free(pixels);
	cartridge_destroy(emulator_remove_cartridge(emulator));
	emulator_destroy(emulator);
	SDL_DestroyTexture(buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}