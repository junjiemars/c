#ifndef _GEO_H_
#define _GEO_H_

#include <nore.h>


// make CFLAGS=-DSHARED=1
#if ( MSYS_NT )

	#if ( 0 == SHARED )

		#define GEO_API __declspec(dllexport) __stdcall

	#elif ( 1 == SHARED )

		#define GEO_API __declspec(dllimport) __stdcall

	#endif // end of SHARED

	
	#else

		#define GEO_API

#endif // end of MSYS_NT


#ifdef __cplusplus
extern "C" {
#endif

double GEO_API area_of_rect(double, double);

#ifdef __cplusplus
}
#endif


#endif // _GEO_H_
