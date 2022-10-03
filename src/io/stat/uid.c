#include <_io_.h>
#include <sys/stat.h>


/*
 * check owner/saved uid/gid
 *
 */


int
main(int argc, char **argv)
{
  int          i, rc;
  struct stat  buf;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname> [pathname...]\n",
              basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  for (i = 1; i < argc; i++)
    {
      rc = lstat(argv[i], &buf);
      if (rc == -1)
        {
          perror(argv[i]);
          continue;
        }

      printf("%s: uid(%d)", argv[i], buf.st_uid);
      printf(",suid(%d)", buf.st_mode & S_ISUID);
      printf(",sgid(%d)\n", buf.st_mode & S_ISGID);

    }


  exit(EXIT_SUCCESS);
}
