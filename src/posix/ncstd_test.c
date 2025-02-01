#include "ncstd.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if (NM_NEED_ENVIRON)
extern char **environ;
#endif

int
main (void)
{
#if defined(__STDC__)
  printf ("%s=%i\n", _str_ (__STDC__), (__STDC__ + 0));
#else
  printf ("%s=(no symbol)\n", _str_ (__STDC__));
#endif

#if defined(__STDC_VERSION__)
  printf ("%s=%liL\n", _str_ (__STDC_VERSION__), (__STDC_VERSION__ + 0L));
#else
  printf ("%s=(no symbol)\n", _str_ (__STDC_VERSION__));
#endif

#if defined(NM_NEED_ENVIRON)
  printf ("%s=%d\n", _str_ (NM_NEED_ENVIRON), NM_NEED_ENVIRON);
#else
  printf ("%s=(no symbol)\n", _str_ (NM_NEED_ENVIRON));
#endif

#if (MSVC)
#pragma warning(disable : 4996)
#endif

  setenv ("XYZ", "abc", 1);
  assert (strcmp ("abc", getenv ("XYZ")) == 0 && "should set XYZ=abc");
  assert (environ && "environ should be a valid pointer");

  /* _hton16_t */
#if (NM_CPU_LITTLE_ENDIAN)
  assert (_hton16_ (0x1122) == (uint16_t)0x2211);
  assert (_hton32_ (0x11223344) == (uint32_t)0x44332211);
  assert (_hton64_ (0x1122334455667788) == (uint64_t)0x8877665544332211);
#endif

  return 0;
}
