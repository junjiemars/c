#include "_signal_.h"

/*
 * 1. `abort(3)' never return to its caller.
 *
 * 2. output streams are flushed and closed is implementation defined.
 *
 * 3. if `on_sig_abrt' returns, `abort(3)' terminates the process.
 *
 */

extern void  abort(void);

__attribute__((unused)) static void  on_sig_abrt(int);


int
main(void)
{
  setvbuf(stdout, NULL, _IOFBF, 0);

  printf("%d\n", getpid());

#if (_IGNORE_SIG_ABRT_)
  struct sigaction  act;

  if (sigaction(SIGABRT, NULL, &act) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  if (act.sa_handler != SIG_IGN)
    {
      act.sa_handler = SIG_IGN;
    }

#else
  signal(SIGABRT, on_sig_abrt);

#endif

  abort();

  /* never go here; */
}

void
on_sig_abrt(int signo)
{
  printf("# %s(%d)\n", _str_(SIGABRT), signo);

  /* cleanup then exit*/

#if (_EXIT_SIG_HANDLER_)
  exit(EXIT_SUCCESS);

#endif
}
