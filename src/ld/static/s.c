#include "_ld_.h"


#define SS  "abc\n"


int
main(void)
{
  ssize_t  rc;

  rc = write(STDOUT_FILENO, SS, sizeof(SS)-1);
  if (rc == -1)
    {
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
