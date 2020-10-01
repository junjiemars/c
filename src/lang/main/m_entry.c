#include <_lang_.h>
#include <stdio.h>

#if (GCC) && (LINUX)
#  define entry main
#endif

#if (MSVC)
FILE* __cdecl __iob_func(void) {
  static FILE _iob[] = { *stdin, *stdout, *stderr };
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
