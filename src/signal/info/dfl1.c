#include "_signal_.h"
#include "sig2str.h"

static void print_sigset (const sigset_t *);

int
main (void)
{
  sigset_t oset;

  if (sigprocmask (SIG_BLOCK, NULL, &oset) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  printf ("default blocked signals:\n------------\n");
  print_sigset (&oset);

  sigfillset (&oset);
  if (sigprocmask (SIG_SETMASK, &oset, NULL) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  printf ("fillset blocked signals:\n------------\n");
  print_sigset (&oset);

  exit (EXIT_SUCCESS);
}

void
print_sigset (const sigset_t *set)
{
  int n = 0;

  setvbuf (stdout, NULL, _IOFBF, 0);

  for (int i = 1; i < N_SIG2STR; i++)
    {
      if (sigismember (set, i))
        {
          char *d;
          char s[SIG2STR_MAX];

          if (sig2str (i, s) == -1)
            {
              perror (NULL);
              continue;
            }
          d = strsignal (i);
          printf ("SIG%-16s: [%02i] %s\n", s, i, d);
          n++;
        }
    }

  setvbuf (stdout, NULL, _IONBF, 0);
  printf ("------------\ntotal: %d\n", n);
}
