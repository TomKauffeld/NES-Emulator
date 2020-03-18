#ifndef VISPA_API
#ifdef VISPA_EXPORTS
#define VISPA_API __declspec(dllexport)
#else
#define VISPA_API __declspec(dllimport)
#endif
#endif