#include "../_lang_.h"
#include <signal.h>

/**
 * 1. Using old fashion of `signal' at here, see src/signal for more
 * about signals.
 *
 * 2. On Windows there are no the exact equivalent of Unix signals.
 *
 */

#if (MSVC)
#pragma warning(disable : 4996) /* _CRT_SECURE_NO_WARNINGS */
#endif

#if (WINNT)
static void psignal (int sig, const char *s);
#endif

#if !defined(N) || (N < 0)
#define N 8
#endif /* N */

typedef void (*on_signal) (int);

static volatile int s_flag = 0;

static void on_sigint_stop (int sig);
static void on_sigint_continue (int sig);
static void on_sigterm_continue (int sig);

int
main (void)
{
  printf ("pid=%d\n", getpid ());

  if (signal (SIGINT, on_sigint_continue) == SIG_ERR)
    {
      perror ("!panic, signal");
      return 1;
    }
  if (signal (SIGTERM, on_sigterm_continue) == SIG_ERR)
    {
      perror ("!panic, signal");
      return 1;
    }

  for (int n = 0; n < N; n++)
    {
      if (s_flag)
        {
          fprintf (stderr, "stop, s_flag = %i\n", s_flag);
          break;
        }
      if (3 == n)
        {
          int rc = raise (SIGINT);
          if (rc)
            {
              perror ("!panic, raise SIGINT");
            }
        }
      if (5 == n)
        {
          int rc = raise (SIGTERM);
          if (rc)
            {
              perror ("!panic, raise SIGTERM");
            }
        }
      else
        {
          fprintf (stderr, "sleeping 1s (%i/%i)...\n", n + 1, N);
        }
      sleep (1);
    }

  return 0;
}

#if (WINNT)
void
psignal (int sig, const char *s)
{
  static char *tbl[] = {
    "default",   0,
    "interrupt",                        /* SIGINT */
    0,           "illegal instruction", /* SIGILL */
    0,
  };

  char *msg = (sig < 0 || sig >= sizeof (tbl) / sizeof (*tbl))
                  ? "Unknown signal"
                  : tbl[sig];

  if (0 == s || '\0' == s[0])
    {
      fprintf (stderr, "%s\n", msg);
    }
  else
    {
      fprintf (stderr, "%s: %s\n", s, msg);
    }
}
#endif /* end of psignal */

void
on_sigint_stop (int sig)
{
  psignal (sig, "^ on_sigint_stop");
  s_flag = sig;
}

void
on_sigint_continue (int sig)
{
  psignal (sig, "^ on_sigint_continue");
  /* continue put into pending signals */
  signal (sig, on_sigint_stop);
}

void
on_sigterm_continue (int sig)
{
  psignal (sig, "^ on_sigterm_continue");
  signal (sig, on_sigint_stop);
}
