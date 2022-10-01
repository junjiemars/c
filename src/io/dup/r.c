#include <_io_.h>

static char  buf[BUFSIZ];

int
main(void)
{
  int  n;
  int  fd;

  fd = dup(STDIN_FILENO);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(fd == 3);

  while ((n = read(fd, buf, BUFSIZ)) > 0)
    {
      if (write(STDOUT_FILENO, buf, n) != n)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  exit(EXIT_SUCCESS);
}
