#include "_wasm_.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

EMSCRIPTEN_KEEPALIVE
int
print_file(const char *file) {
  FILE *in = fopen(file, "rb");
  if (!in) {
    perror(0);
    return 0;
  }

  int n = 0;
  int c;
  while (EOF != (c = fgetc(in))) {
    putchar(c);
    n++;
  }

  if (in) {
    fclose(in);
  }
  return n;
}

#ifdef __cplusplus
} /* end of extern "C" */
#endif

#if !__EMSCRIPTEN__
int
main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(stderr, "where input file located?\n");
    return 0;
  }
  print_file(argv[1]);
  return 0;
}
#endif
