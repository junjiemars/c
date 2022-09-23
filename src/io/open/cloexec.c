#include <_io_.h>

int
main(int argc, char **argv)
{
  int    fd;
  int    oflags       =  0;
  int    opt_cloexec  =  0;
  pid_t  pid;


  if (argc < 2)
    {
      printf("usage: <pathname> [0|1]\n");
      exit(EXIT_FAILURE);
    }
  if (argc > 2)
    {
      sscanf(argv[2], "%d", &opt_cloexec);
    }

  oflags = O_WRONLY | O_CREAT | O_TRUNC;
  if (opt_cloexec > 0)
    {
      oflags |= O_CLOEXEC;
    }

  fd = open(argv[1], oflags, S_IREAD);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  pid = fork();
  if (pid)
    {
      if (write(fd, "abc", sizeof("abc")-1) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }
  else
    {
      if (write(fd, "ABC", sizeof("ABC")-1) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  exit(EXIT_SUCCESS);
}
