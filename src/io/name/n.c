#include <_io_.h>


int
main(int argc, char **argv)
{

#if (NAME_MAX)
  printf("NAME_MAX=%lu\n", (unsigned long) NAME_MAX);
#else
  printf("NAME_MAX=(no symbol)\n");
#endif

#if (_POSIX_NAME_MAX)
  printf("_POSIX_NAME_MAX=%lu\n", (unsigned long) _POSIX_NAME_MAX);
#else
  printf("_POSIX_NAME_MAX=(no symbol)\n");
#endif

#if (_POSIX_NO_TRUNC)
  printf("_POSIX_NO_TRUNC=%lu\n", (unsigned long) _POSIX_NO_TRUNC);
#else
  printf("_POSIX_NO_TRUNC=(no symbol)\n");
#endif

  if (argc < 2)
    {
      printf("usage: <pathname>\n");
      exit(EXIT_FAILURE);
    }

  int fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror(NULL);
    }

  exit(EXIT_SUCCESS);
}
