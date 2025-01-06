#include "../_data_.h"
#include <pwd.h>

/*
 * getpwnam1 is an emulatation of `getpwnam'.
 *
 */

extern void print_passwd (const struct passwd *);

static struct passwd *getpwnam1 (const char *);

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf (stderr, "usage: <login...>\n");
      exit (EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      struct passwd *pwd;

      errno = 0;
      if ((pwd = getpwnam1 (argv[i])) == NULL)
        {
          if (errno)
            {
              perror (NULL);
            }

          continue;
        }

      print_passwd (pwd);
    }

  exit (EXIT_SUCCESS);
}

struct passwd *
getpwnam1 (const char *name)
{
  struct passwd *p;

  setpwent ();

  while ((p = getpwent ()) != NULL)
    {
      if (strcmp (name, p->pw_name) == 0)
        {
          break;
        }
    }

  endpwent ();

  return p;
};
