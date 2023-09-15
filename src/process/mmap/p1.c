#include "_process_.h"


int
main (void)
{
  char *p;
  int page_size = getpagesize ();

  if ((p = mmap (NULL, page_size, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0))
      == (void *)-1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("%p\n", p);

  if (mprotect (p, page_size, PROT_READ) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}
