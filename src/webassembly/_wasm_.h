#ifndef _WASM_H_
#define _WASM_H_

#include <nore.h>

#ifdef __EMSCRIPTEN__
#  include <emscripten.h>
/* #  ifdef EMSCRIPTEN_KEEPALIVE */
/* #    undef EMSCRIPTEN_KEEPALIVE */
/* #  endif */
#endif


#define _unused_(x) (void)(x)


#endif /* end of _WASM_H_ */
