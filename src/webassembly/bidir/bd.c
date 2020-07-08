#include "_wasm_.h"

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE
int
ver(void) {
  return 0x11223344;
}
  
EMSCRIPTEN_KEEPALIVE
void
console_log(void) {
  EM_ASM({
      console.log("OK, console.log output");
  });
}

EMSCRIPTEN_KEEPALIVE
int
incf(int i) {
  int x = EM_ASM_INT({
      console.log("incf(%i)", $0);
      return $0 + 1;
  }, i);
  return x;
}


#ifdef __cplusplus
} /* end of extern "C" */
#endif


int
main(void) {
  return 0;
}
