#include <_io_.h>

/*
 *
 */

int
main(int argc, char **argv)
{
  int  fd;

  if (argc < 2)
    {
      printf("usage <pathname> [dir...]\n");
      exit(EXIT_SUCCESS);
    }

  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  for (int i = 2; i < argc; i++)
    {
      if (mkdirat(fd, argv[i], S_IRUSR | S_IWUSR | S_IXUSR) == -1)
        {
          perror(NULL);
          continue;
        }
    }


  exit(EXIT_SUCCESS);

}
