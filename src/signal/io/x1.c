#include "_signal_.h"
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/stat.h>
#include <unistd.h>

static void on_sig_xfsz (int);

int
main (void)
{
  ssize_t r, w;
  char buf[BUF_SIZE];
  struct stat ss;
  struct rlimit fsz;
  struct sigaction nset;

  fprintf (stderr, "|> %d, BUF_SIZE=%i, FIL_SIZE=%i\n", getpid (), BUF_SIZE,
           FIL_SIZE);

  if (fstat (STDIN_FILENO, &ss) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  fprintf (stderr, "|> stdin file size %zu bytes\n", (size_t)ss.st_size);

  if (getrlimit (RLIMIT_FSIZE, &fsz) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  fsz.rlim_cur = FIL_SIZE;

  if (setrlimit (RLIMIT_FSIZE, &fsz) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  fprintf (stderr, "|> setrlmit %s = { .rlim_cur = %llu, .rlim_max = %llu }\n",
           _str_ (RLIMIT_FSIZE), (unsigned long long)fsz.rlim_cur,
           (unsigned long long)fsz.rlim_cur);

  nset.sa_handler = on_sig_xfsz;
  sigemptyset (&nset.sa_mask);
  nset.sa_flags = 0;
#ifdef SA_INTERRUPT
  nset.sa_flags |= SA_INTERRUPT;
#endif

  if (sigaction (SIGXFSZ, &nset, NULL) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  while ((r = read (STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
      errno = 0;
      if ((w = write (STDOUT_FILENO, buf, r)) != r)
        {
          if (errno)
            {
              perror ("! write");
            }
          fprintf (stderr, "r(%zd), w(%zd)\n", r, w);
          exit (EXIT_FAILURE);
        }
    }

  if (r < 0)
    {
      perror ("! read");
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}

void
on_sig_xfsz (int signo)
{
  /* SIGXFSZ never be caught on Drawin */
  fprintf (stderr, "|> caught %s(%d)\n", _str_ (SIGXFSZ), signo);
}
