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

static void  on_sig_abrt(int);


int
main(void)
{
  setvbuf(stdout, NULL, _IOFBF, 0);

  printf("%d\n", getpid());

  signal(SIGABRT, on_sig_abrt);

  abort();

  /* never go here; */
}

void
on_sig_abrt(int signo)
{
  printf("# %s(%d)\n", _str_(SIGABRT), signo);

  /* cleanup then exit*/

  exit(EXIT_SUCCESS);
}
