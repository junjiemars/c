#include "_signal_.h"



int
main(void)
{
  sigset_t  oset;

  if (sigprocmask(SIG_BLOCK, NULL, &oset) < 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
