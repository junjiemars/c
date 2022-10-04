#include <_io_.h>

int
main(void)
{
#if defined(_POSIX_CHOWN_RESTRICTED)
  printf("%s=%ld\n", _str_(_POSIX_CHOWN_RESTRICTED),
         (long int) _POSIX_CHOWN_RESTRICTED);
#else
  printf("%_POSIX_CHOWN_RESTRICTED=(no symbol)\n");
#endif

  exit(EXIT_SUCCESS);
}
