#ifndef __VISPA_H__
#define __VISPA_H__

#ifdef VISPA_EXPORTS
#define VISPA_API __declspec(dllexport)
#else
#define VISPA_API __declspec(dllimport)
#endif

struct vispa;
typedef struct vispa Vispa;

VISPA_API Vispa* vispa_init(int width, int height, const char* title);


VISPA_API void vispa_destroy(Vispa* vispa);


#endif