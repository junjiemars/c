#ifndef _WASM_H_
#define _WASM_H_

#include <nore.h>

#if __EMSCRIPTEN__
#  include <emscripten.h>
#else
#  define EMSCRIPTEN_KEEPALIVE
#  define EM_ASM(...)
#  define EM_ASM_INT(code, ...) __VA_ARGS__
#endif


#define _unused_(x) (void)(x)


#endif /* end of _WASM_H_ */
