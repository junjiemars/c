#include "_data_.h"
#include <grp.h>

/*
 * getgrgid1 is an emulation of `getgrgid'.
 *
 *
 */

extern void  print_group(const struct group *);

static struct group  *getgrgid1(uid_t);


int
main(int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <gid...>\n");
      exit(EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      struct group  *g;

      errno = 0;
      if ((g = getgrgid1((gid_t) atoi(argv[i]))) == NULL)
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
getgrgid1(uid_t gid)
{
  struct group  *g;

  setgrent();

  while ((g = getgrent()) != NULL)
    {
      if (gid == g->gr_gid)
        {
          break;
        }
    }

  endgrent();

  return g;
}
