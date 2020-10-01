#include <_lang_.h>
#include <stdio.h>

#if (GCC) || (MSVC)
#  if (LINUX) || (WINNT)
#    define entry main
#  endif
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
