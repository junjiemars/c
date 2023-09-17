#include "_signal_.h"

/*
 * 1. `abort(3)' never return to its caller.
 *
 * 2. The output streams are flushed and closed is implementation
 * defined.
 *
 * 3. If `on_sig_abrt' returns, `abort(3)' terminates the process.
 *
 */

extern void abort (void);

#if !defined(_IGN_SIG_ABRT_) || (_IGN_SIG_ABRT_ < 0)
static void on_sig_abrt (int);
static void on_abrt_exit (void);
#endif

int
main (void)
{
  struct sigaction oact;

  setvbuf (stdout, NULL, _IOFBF, 0);
  printf ("%d\n", getpid ());

#if !defined(_IGN_SIG_ABRT_) || (_IGN_SIG_ABRT_ < 0)
  atexit (on_abrt_exit);
#endif

  if (sigaction (SIGABRT, NULL, &oact) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

#if defined(_IGN_SIG_ABRT_) && (_IGN_SIG_ABRT_ > 0)
  if (act.sa_handler != SIG_IGN)
    {
      act.sa_handler = SIG_IGN;
    }
#elif defined(_IGN_SIG_ABRT_) && (_IGN_SIG_ABRT_ == 0)
    /* SIG_DFL*/
#else
  signal (SIGABRT, on_sig_abrt);
#endif

  abort ();

  /* never go here; */
}

#if !defined(_IGN_SIG_ABRT_) || (_IGN_SIG_ABRT_ < 0)

void
on_sig_abrt (int signo)
{
  printf ("# %s(%d)\n", _str_ (SIGABRT), signo);

  /* cleanup then exit*/

#if (_EXIT_SIG_HANDLER_ > 0)
  exit (EXIT_SUCCESS);
#endif
}

void
on_abrt_exit (void)
{
  printf ("# exiting ...\n");
}

#endif /* _IGN_SIG_ABRT_ < 0 */
