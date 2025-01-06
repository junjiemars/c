#ifndef _MACRO_H_
#define _MACRO_H_

#include "../_lang_.h"

#if MSVC
#define W_C4100(a)                                                            \
  {                                                                           \
    (a);                                                                      \
  }
#endif

#endif // _MACRO_H_
