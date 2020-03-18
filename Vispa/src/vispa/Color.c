#include "Color.h"
#include "Vispa.h"


uint8_t vispa_get_red(uint32_t color)
{
	return (color >> 24) & 0x000000FF;
}

uint8_t vispa_get_green(uint32_t color)
{
	return (color >> 16) & 0x000000FF;
}

uint8_t vispa_get_blue(uint32_t color)
{
	return (color >> 8) & 0x000000FF;
}

uint8_t vispa_get_alpha(uint32_t color)
{
	return (color >> 0) & 0x000000FF;
}

uint32_t vispa_get_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
	return (red << 24) | (green << 16) | (blue << 8) | (alpha << 0);
}


void vispa_set_pixel_color(Vispa* vispa, int x, int y, uint32_t color)
{
	if (vispa == NULL)
		return;
	if (x < 0 || y < 0 || x >= vispa->width || y >= vispa->height)
		return;
	vispa->buffer[x + y * vispa->width] = color;
}

void vispa_set_pixel_rgb(Vispa* vispa, int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
	vispa_set_pixel_color(vispa, x, y, vispa_get_color(red, green, blue, 0x00));
}
