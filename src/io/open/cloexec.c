#include <_io_.h>

int
main(int argc, char **argv)
{
  int  fd;
  int  oflags       =  0;
  int  opt_cloexec  =  0;

  if (argc < 2)
    {
      printf("usage: <pathname> [0|1]\n");
      exit(EXIT_FAILURE);
    }
  if (argc >= 2)
    {
      sscanf(argv[2], "%d", &opt_cloexec);
    }

  oflags = O_WRONLY;
  if (opt_cloexec > 0)
    {
      oflags = O_WRONLY | O_CLOEXEC;
    }

  fd = open(argv[1], oflags);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);
}
