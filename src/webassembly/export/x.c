#include "_wasm_.h"

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE
int
version(void) {
  return 0x11223344;
}

EMSCRIPTEN_KEEPALIVE
int
sum(int n, int acc) {
  if (n < 1) {
    return acc;
  }
  return sum(n-1, n+acc);
}

#ifdef __cplusplus
} /* end of extern "C" */
#endif

