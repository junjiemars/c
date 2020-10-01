#include <_lang_.h>
#include <stdio.h>

#if (GCC) && (LINUX)
#  define entry main
#endif

#if (MSVC)
#include <stdlib.h>
FILE* __cdecl __iob_func(void) {
  static FILE _iob[] = malloc(sizeof(*stdin)*3);
  _iob[0] = *stdin;
  _iob[1] = *stdout;
  _iob[2] = *stderr;
  return _iob;
}
#endif

int
entry(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

  printf("enter entry...\n");

  return 0;
}

#if (GCC) && (LINUX)
#  if defined(entry)
#    undef entry
#  endif
#endif

#ifdef main
#undef main
#endif
