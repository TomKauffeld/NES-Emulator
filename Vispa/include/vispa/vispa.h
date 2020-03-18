#ifndef __VISPA_H__
#define __VISPA_H__

#ifdef VISPA_EXPORTS
#define VISPA_API __declspec(dllexport)
#else
#define VISPA_API __declspec(dllimport)
#endif

#include <utils/boolean.h>

struct vispa;
typedef struct vispa Vispa;

typedef void(on_frame_fun)(Vispa* vispa);

VISPA_API Vispa* vispa_init(int width, int height, const char* title, on_frame_fun* on_frame);

VISPA_API bool vispa_should_close(Vispa* vispa);

VISPA_API void vispa_tick_once(Vispa* vispa);

VISPA_API void vispa_tick_automatic(Vispa* vispa);

VISPA_API void vispa_destroy(Vispa* vispa);


#endif