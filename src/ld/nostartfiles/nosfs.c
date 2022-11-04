#include "_ld_.h"


#define SS  "enter _start ...\n"


int
_start(void)
{
  ssize_t  n;

  n = write(STDOUT_FILENO, SS, sizeof(SS)-1);
  if (n == -1)
    {
      _exit(EXIT_FAILURE);
    }

  _exit(EXIT_SUCCESS);
}
