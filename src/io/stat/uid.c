#include "_io_.h"
#include <sys/stat.h>

/*
 * check the uid/gid of the owner/saved.
 *
 */

#define uid_c(m) (((m) & S_ISUID) == S_ISUID) ? '*' : '_'
#define gid_c(m) (((m) & S_ISGID) == S_ISGID) ? '*' : '_'

int
main (int argc, char **argv)
{
  int          rc;
  struct stat  ss;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <pathname...>\n", basename(argv[0]));
      exit (EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      rc = lstat (argv[i], &ss);
      if (rc == -1)
        {
          perror (argv[i]);
          continue;
        }

      printf ("%s: uid(%d)", argv[i], ss.st_uid);
      printf (",gid(%d)", ss.st_gid);
      printf (",suid(%c)", uid_c (ss.st_mode));
      printf (",sgid(%c)\n", gid_c (ss.st_mode));
    }

  exit (EXIT_SUCCESS);
}
