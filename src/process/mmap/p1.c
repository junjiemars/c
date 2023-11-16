#include "_process_.h"

int
main (void)
{
  char *p;
  int page_size = getpagesize ();

  if ((p = mmap (NULL, page_size, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0))
      == MAP_FAILED)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("%p %p\n", p, &p);

  if (mprotect (p, page_size, PROT_READ) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  if (munmap (p, page_size) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}
