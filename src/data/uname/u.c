#include "../_data_.h"
#include <sys/utsname.h>

/*
 * uname(2), uname(1).
 *
 */

int
main (void)
{
  struct utsname nam = { 0 };

  if (uname (&nam) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  printf ("sysname: %s\n"
          "nodename: %s\n"
          "release: %s\n"
          "version: %s\n"
          "machine: %s\n",
          nam.sysname, nam.nodename, nam.release, nam.version, nam.machine);

  exit (EXIT_SUCCESS);
}
