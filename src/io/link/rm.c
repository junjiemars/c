#include <_io_.h>

/*
 * 1. `remove' is an ISO function and `rmdir' is a system call.
 *
 * 2. For a file, `remove' is identical to `unlink'. For a directory
 * `remove' is indentical to `rmdir'.
 *
 */


int
main(int argc, char **argv)
{
  struct stat  ss;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <dir>\n");
      exit(EXIT_FAILURE);
    }

  if (lstat(argv[1], &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (S_ISREG(ss.st_mode) || S_ISDIR(ss.st_mode))
    {
      if (remove(argv[1]) == -1)
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

  printf("rm %s(%c), ", argv[1], S_ISREG(ss.st_mode) ? 'f' : 'd');
  printf("done\n");


  exit(EXIT_SUCCESS);
}
