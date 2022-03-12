#include "_io_.h"

int
main(void)
{
  int   n;
  char  buf[64];

  while ((n = read(STDIN_FILENO, buf, sizeof(buf) - 1)) > 0)
    {
      if (write(STDOUT_FILENO, buf, n) != n)
        {
          perror("!write error");
          exit(EXIT_FAILURE);
        }
    }

  if (n == -1)
    {
      perror("!read error");
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);

}
