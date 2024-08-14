#include "_ipc_.h"

void pr_hostent (struct hostent *);

int
main (void)
{
  struct hostent *h;

  while ((h = gethostent ()) != 0)
    {
      pr_hostent (h);
    }

  endhostent ();

  exit (EXIT_SUCCESS);
}

void
pr_hostent (struct hostent *ent)
{
  printf ("h_name: %s\n", ent->h_name);
  printf ("h_aliases:\n");
  for (char **ss = ent->h_aliases; *ss != 0; ss++)
    {
      printf ("  %s\n", *ss);
    }
  printf ("h_addrtype: %d\n", ent->h_addrtype);
  printf ("h_length: %d\n", ent->h_length);
  printf ("h_addr_list:\n");
  for (char **ss = ent->h_addr_list; *ss != 0; ss++)
    {
      printf ("  %s\n", *ss);
    }
}
