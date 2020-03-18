#ifndef __VISPA_COLOR_INTERN_H__
#define __VISPA_COLOR_INTERN_H__
#include <vispa/color.h>

uint8_t vispa_get_red(uint32_t color);

uint8_t vispa_get_green(uint32_t color);

uint8_t vispa_get_blue(uint32_t color);

uint8_t vispa_get_alpha(uint32_t color);

uint32_t vispa_get_color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

#endif