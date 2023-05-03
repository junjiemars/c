#include "_io_.h"
#include <fcntl.h>

/*
 * faccessat samed as access if:
 * 1. faccessat(AT_FDCWD,...).
 * 2. faccessat(any, /absolute, ...).
 *
 * faccessat(,,,flag=AT_EACCESS) using effective uid/gid.
 */

int
main (int argc, char **argv)
{
  int rc;
  uid_t uid, euid;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <pathname> [pathname...]\n",
               basename (argv[0]));
      exit (EXIT_FAILURE);
    }

  uid = getuid ();
  euid = geteuid ();

  printf ("uid(%i),euid(%i)\n------------\n", uid, euid);

  for (int i = 1; i < argc; i++)
    {
      rc = faccessat (AT_FDCWD, argv[i], F_OK, 0);
      if (rc == -1)
        {
          perror ("!exist access");
        }

      rc = faccessat (AT_FDCWD, argv[i], R_OK, 0);
      if (rc == -1)
        {
          perror ("!read access");
        }

      rc = faccessat (AT_FDCWD, argv[i], R_OK, AT_EACCESS);
      if (rc == -1)
        {
          perror ("!read access (effective)");
        }

      rc = open (argv[i], O_RDONLY);
      if (rc == -1)
        {
          perror ("!open for read");
        }
    }

  exit (EXIT_SUCCESS);
}
