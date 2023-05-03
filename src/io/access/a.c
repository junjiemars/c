#include "_io_.h"

/*
 * 1. access just check real user/group-id.
 * 2. open check effective user/group-id.
 *
 * References:
 * 1.
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/access.html#tag_16_09
 *
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

  printf ("uid: %i, euid: %i\n------------\n", uid, euid);

  for (int i = 1; i < argc; i++)
    {
      rc = access (argv[i], F_OK);
      if (rc == -1)
        {
          perror ("!exist access");
        }

      rc = access (argv[i], X_OK);
      if (rc == -1)
        {
          perror ("!execute access");
        }

      rc = access (argv[i], R_OK);
      if (rc == -1)
        {
          perror ("!read access");
        }

      rc = open (argv[i], O_RDONLY);
      if (rc == -1)
        {
          perror ("!open for read");
        }
    }

  exit (EXIT_SUCCESS);
}
