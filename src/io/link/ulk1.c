#include <_io_.h>

int
main(int argc, char **argv)
{
  int          fd;
  struct stat  ss;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <path|file>\n");
      exit(EXIT_FAILURE);
    }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (fstat(fd, &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (S_ISREG(ss.st_mode))
    {
      if (unlink(argv[1]) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }
  else if (S_ISDIR(ss.st_mode))
    {
      if (unlinkat(AT_FDCWD, argv[1], AT_REMOVEDIR) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }
  else
    {
      printf("# skip ...\n");
      exit(EXIT_SUCCESS);
    }

  printf("unlink %s(%c)... ", argv[1], S_ISREG(ss.st_mode) ? 'f' : 'd');
  printf("done\n");


  exit(EXIT_SUCCESS);
}
