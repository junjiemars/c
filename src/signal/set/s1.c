#include <_signal_.h>

int
main(void)
{
  sigset_t  oset;

  if (-1 == sigprocmask(SIG_BLOCK, NULL, &oset))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
