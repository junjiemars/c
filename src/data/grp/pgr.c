#include "_data_.h"
#include <grp.h>

void
print_group (const struct group *grp)
{
  printf ("name: %s\n"
          "passwd: %s\n"
          "gid: %li\n",
          grp->gr_name, grp->gr_passwd, (long)grp->gr_gid);

  printf ("members: ");

  for (char **p = grp->gr_mem; *p != NULL; p++)
    {
      printf ("%s ", *p);
    }

  printf ("\n");
}
