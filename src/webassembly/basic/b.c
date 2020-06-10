#include "_wasm_.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE
int
version() {
  return 0x11223344;
}

EMSCRIPTEN_KEEPALIVE
int
add_10(int x) {
  return x+10;
}
  
EMSCRIPTEN_KEEPALIVE
size_t
fact(size_t n, size_t i, size_t acc) {
  if (i > n) {
    return acc;
  }
  return fact(n, i+1, i*acc);
}

#ifdef __cplusplus
} /* end of extern "C" */
#endif

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

#if __EMSCRIPTEN__
  printf("Hello, WASM, __EMSCRIPTEN__=%d\n", __EMSCRIPTEN__);
#else
  printf("Hello, WASM\n");
#endif

  printf("fact(%zu) = %zu\n", 10ul, fact(10, 1, 1));
  
  return 0;
}
