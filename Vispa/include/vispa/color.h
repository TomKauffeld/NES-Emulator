#ifndef __VISPA_COLOR_H__
#define __VISPA_COLOR_H__
#include "vispa.h"


VISPA_API void vispa_set_pixel_color(Vispa* vispa, int x, int y, uint32_t color);

VISPA_API void vispa_set_pixel_rgb(Vispa* vispa, int x, int y, uint8_t red, uint8_t green, uint8_t blue);


#endif