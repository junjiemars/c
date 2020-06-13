#include "_wasm_.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE
int
ver(void) {
  return 0x11223344;
}

EMSCRIPTEN_KEEPALIVE
const char*
hello(void) {
  return "Hello, WASM";
}

EMSCRIPTEN_KEEPALIVE
const char*
mark_a(char *ss) {
  ss[0] = 'A';
  return &ss[0];
}


#ifdef __cplusplus
} /* end of extern "C" */
#endif


#if !__EMSCRIPTEN__
int
main(void) {
  printf("ver() = %i\n", ver());
  printf("hello() = %s\n", hello());
  char ss[] = "Hello";
  printf("mark_a(%s) = %s\n", ss, mark_a(ss));
  return 0;
}
#endif
