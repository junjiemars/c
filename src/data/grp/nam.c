#include "_data_.h"
#include <grp.h>

/*
 * getgrnam1 is an emulation of `getgrnam'.
 *
 *
 */

extern void  print_group(const struct group *);

static struct group  *getgrnam1(const char *);


int
main(int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <group...>\n");
      exit(EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      struct group  *g;

      errno = 0;
      if ((g = getgrnam1(argv[i])) == NULL)
        {
          if (errno)
            {
              perror(NULL);
            }
          continue;
        }

      print_group(g);
    }

  exit(EXIT_SUCCESS);
}

struct group *
getgrnam1(const char *name)
{
  struct group  *g;

  setgrent();

  while ((g = getgrent()) != NULL)
    {
      if (strcmp(name, g->gr_name) == 0)
        {
          break;
        }
    }

  endgrent();

  return g;
}
