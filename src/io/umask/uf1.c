#include "_io_.h"


static mode_t get_umask(void);

int
main(void)
{
  mode_t m;

  m = get_umask();
  printf("0%o\n", m);

  exit(EXIT_SUCCESS);
}


mode_t
get_umask(void)
{
  mode_t rc = umask(022);
  umask(rc);
  return rc;
}
