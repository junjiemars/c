#include <_io_.h>

int
main(int argc, char **argv)
{
  ssize_t  n;
  char     ss[PATH_MAX] = {0};

  if (argc < 2)
    {
      fprintf(stderr, "usage: <pathname>\n");
      exit(EXIT_FAILURE);
    }

  n = readlinkat(AT_FDCWD, argv[1], ss, PATH_MAX);
  if (n == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("%s\n", ss);


  exit(EXIT_SUCCESS);
}
