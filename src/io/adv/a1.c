#include "_io_.h"

int
main (void)
{
  int fd = STDIN_FILENO;
  int n;
  char buf [64];

#if (NM_HAVE_POSIX_FADVISE)
  if (posix_fadvise (fd, 0, 0, POSIX_FADV_SEQUENTIAL) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
#endif

  while ((n = read (fd, buf, sizeof (buf))) > 0)
    {
      write (STDOUT_FILENO, buf, n);
    }

  return 0;
}
