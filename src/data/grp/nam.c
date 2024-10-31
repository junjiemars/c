#include "_data_.h"
#include <grp.h>

/*
 * getgrnam1 is an emulation of `getgrnam'.
 *
 *
 */

extern void print_group (const struct group *);

static struct group *getgrnam1 (const char *, struct group *);

int
main (int argc, char *argv[])
{
  struct group g;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <group...>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      errno = 0;
      if (getgrnam1 (argv[i], &g) == NULL)
        {
          if (errno)
            {
              perror (NULL);
            }
          continue;
        }

      print_group (&g);
    }

  exit (EXIT_SUCCESS);
}

struct group *
getgrnam1 (const char *name, struct group *grp)
{
  struct group *g;

  setgrent ();

  while ((g = getgrent ()) != NULL)
    {
      if (strcmp (name, g->gr_name) == 0)
        {
          *grp = *g;
          endgrent ();
          return grp;
        }
    }

  endgrent ();
  return NULL;
}
