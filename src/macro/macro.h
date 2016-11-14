
#ifndef _MACRO_H_
#define _MACRO_H_

#include <nm_auto_config.h>
#include <nm_auto_headers.h>

#if (MSYS_NT)
	
	#if (CC_MSVC)
		#define W_C4100(a) { (a); }
	#endif

#endif

#endif // _MACRO_H_
