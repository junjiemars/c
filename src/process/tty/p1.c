#include "_process_.h"

int
main(int argc, char *argv[])
{
  int    fd;
  char  *name;

  if (argc < 2)
    {
      fd = STDIN_FILENO;
    }
  else
    {
      fd = atoi(argv[1]);
    }

  if (isatty(fd) == 1)
    {
      name = ttyname(fd);
      if (name == NULL)
        {
          perror("ttyname");
          exit(1);
        }
      printf("%d is a tty: %s\n", fd, name);
    }
  else
    {
      if (errno)
        {
          perror(NULL);
        }
      printf("%d is not a tty\n", fd);
    }

  exit(0);
}
