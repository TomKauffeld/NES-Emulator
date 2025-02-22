#ifndef __EMULATOR_PPU_CORE_PAL_SCREEN_H__
#define __EMULATOR_PPU_CORE_PAL_SCREEN_H__
#include <inttypes.h>

//#define to_color(r, g, b) ((r << 24) + (g << 16) + (b << 8) + 255)
#define to_color(r, g, b) ((255 << 24) + (b << 16) + (g << 8) + r)

uint32_t palScreen[0x40] = {
	to_color(84, 84, 84),
	to_color(0, 30, 116),
	to_color(8, 16, 144),
	to_color(48, 0, 136),
	to_color(68, 0, 100),
	to_color(92, 0, 48),
	to_color(84, 4, 0),
	to_color(60, 24, 0),
	to_color(32, 42, 0),
	to_color(8, 58, 0),
	to_color(0, 64, 0),
	to_color(0, 60, 0),
	to_color(0, 50, 60),
	to_color(0, 0, 0),
	to_color(0, 0, 0),
	to_color(0, 0, 0),
	to_color(152, 150, 152),
	to_color(8, 76, 196),
	to_color(48, 50, 236),
	to_color(92, 30, 228),
	to_color(136, 20, 176),
	to_color(160, 20, 100),
	to_color(152, 34, 32),
	to_color(120, 60, 0),
	to_color(84, 90, 0),
	to_color(40, 114, 0),
	to_color(8, 124, 0),
	to_color(0, 118, 40),
	to_color(0, 102, 120),
	to_color(0, 0, 0),
	to_color(0, 0, 0),
	to_color(0, 0, 0),
	to_color(236, 238, 236),
	to_color(76, 154, 236),
	to_color(120, 124, 236),
	to_color(176, 98, 236),
	to_color(228, 84, 236),
	to_color(236, 88, 180),
	to_color(236, 106, 100),
	to_color(212, 136, 32),
	to_color(160, 170, 0),
	to_color(116, 196, 0),
	to_color(76, 208, 32),
	to_color(56, 204, 108),
	to_color(56, 180, 204),
	to_color(60, 60, 60),
	to_color(0, 0, 0),
	to_color(0, 0, 0),
	to_color(236, 238, 236),
	to_color(168, 204, 236),
	to_color(188, 188, 236),
	to_color(212, 178, 236),
	to_color(236, 174, 236),
	to_color(236, 174, 212),
	to_color(236, 180, 176),
	to_color(228, 196, 144),
	to_color(204, 210, 120),
	to_color(180, 222, 120),
	to_color(168, 226, 144),
	to_color(152, 226, 180),
	to_color(160, 214, 228),
	to_color(160, 162, 160),
	to_color(0, 0, 0),
	to_color(0, 0, 0)
};

#endif