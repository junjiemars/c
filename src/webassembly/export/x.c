#include "_wasm_.h"

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE
unsigned long
ver(void) {
  return 0x11223344;
}

EMSCRIPTEN_KEEPALIVE
unsigned long
sum(unsigned long n, unsigned long acc) {
  if (n < 1) {
    return acc;
  }
  return sum(n-1, n+acc);
}

EMSCRIPTEN_KEEPALIVE
long long
sqr(long long x) {
  return x*x;
}


#ifdef __cplusplus
} /* end of extern "C" */
#endif

#if !__EMSCRIPTEN__
#include <stdio.h>
int
main(void) {
  printf("sqr(%ld) = %lld\n", 10L, sqr(10L));
  return 0;
}
#endif
