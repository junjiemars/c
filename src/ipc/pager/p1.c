#include <_ipc_.h>

#if !defined(DEF_PAGER)
#define DEF_PAGER "/usr/bin/more"
#endif /* DEF_PAGER */

extern int paging (const char *, const char *);

int
main (int argc, char *argv[])
{
  char *pager, *pager_name;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <pathname>\n", argv[0]);
      exit (EXIT_FAILURE);
    }

  if ((pager_name = getenv ("PAGER")) == NULL)
    {
      pager = DEF_PAGER;
    }

  exit (paging (argv[1], pager));
}
