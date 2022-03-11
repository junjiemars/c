#include "_data_.h"

int
main(void)
{
  int   rc;
  char  buf[256];

  rc = gethostname(buf, 256);
  if (rc == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  printf("%s\n", buf);

  exit(EXIT_SUCCESS);
}
