#ifndef _GEO_H_
#define _GEO_H_

#include <nm_auto_config.h>
#include <nm_auto_headers.h>

#if (MSYS_NT)

#define GEO_API __declspec(dllexport) __stdcall

#ifdef __cplusplus
extern "C" {
#endif

double GEO_API area_of_rect(double, double);

#ifdef __cplusplus
}
#endif

#else

#define GEO_API

double area_of_rect(double, double);

#endif // MSYS_NT



#endif // _GEO_H_
