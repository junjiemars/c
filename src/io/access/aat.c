#include "_io_.h"

/*
 * faccessat samed as access if:
 * 1. faccessat(AT_FDCWD,...).
 * 2. faccessat(any, /absolute, ...).
 *
 * faccessat(,,,flag=AT_EACCESS) using effective uid/gid.
 */

#define print_test(m, e, r)                                                   \
  printf ("access %s (%s,%s): %s\n",                                          \
          (m) == F_OK   ? _str_ (F_OK)                                        \
          : (m) == R_OK ? _str_ (R_OK)                                        \
          : (m) == W_OK ? _str_ (W_OK)                                        \
          : (m) == X_OK ? _str_ (X_OK)                                        \
                        : "",                                                 \
          ((e)&AT_EACCESS) == AT_EACCESS ? "effective" : "real",              \
          ((e)&AT_SYMLINK_NOFOLLOW) == AT_SYMLINK_NOFOLLOW ? "nofollow"       \
                                                           : "follow",        \
          (r) == 0 ? "yes" : "no")

int
main (int argc, char **argv)
{
  int rc;
  uid_t uid, euid;
  int modes[] = { F_OK, R_OK, W_OK, X_OK, -1 };
  int flags[] = { 0, AT_EACCESS, AT_SYMLINK_NOFOLLOW,
                  AT_EACCESS | AT_SYMLINK_NOFOLLOW, -1 };

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
      printf ("%s\n", argv[i]);

      for (int *mode = modes; *mode > -1; mode++)
        {
          for (int *flag = flags; *flag > -1; flag++)
            {
              rc = faccessat (AT_FDCWD, argv[i], *mode, *flag);
              print_test (*mode, *flag, rc);
            }
        }

      rc = open (argv[i], O_RDONLY);
      if (rc == -1)
        {
          perror ("!open for readonly");
        }
    }

  exit (EXIT_SUCCESS);
}
