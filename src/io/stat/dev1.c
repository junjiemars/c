#include <_io_.h>

/*
 * Show st_dev and st_rdev.
 *
 */

int
main(int argc, char **argv)
{
  struct stat  ss;

  for (int i = 1; i < argc; i++)
    {
      printf("%s: ", argv[i]);

      if (lstat(argv[i], &ss) == -1)
        {
          printf("%s\n", strerror(errno));
          continue;
        }

      printf("dev = %d/%d", major(ss.st_dev), minor(ss.st_dev));

      if (S_ISCHR(ss.st_mode) || S_ISBLK(ss.st_mode))
        {
          printf(" (%s) rdev = %d/%d",
                 S_ISCHR(ss.st_mode) ? "character" : "block",
                 major(ss.st_rdev), minor(ss.st_rdev));
        }

      printf("\n");
    }

  exit(EXIT_SUCCESS);
}
