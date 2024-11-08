#include "_signal_.h"

/*
 * Extends `read(2)' to support `timeout'.
 *
 * 1. Same as `read(2)' excepts
 * 2. `errno(3)' be set to `ETIMEDOUT' if the `timeout' expires.
 *
 */

ssize_t read3 (int, void *, size_t, int timeout);

static void on_sig_alrm (int signo);

static sigjmp_buf env_alrm;
static sig_atomic_t can_jump;

/*
 * Read `nbyte' bytes from `fd' into `buf' in `timeout' seconds.
 */
ssize_t
read3 (int fd, void *buf, size_t nbyte, int timeout)
{
  sigset_t oset;
  struct sigaction nact;

  /* void current alarm */
  alarm (0);

  sigfillset (&nact.sa_mask);
  sigdelset (&nact.sa_mask, SIGALRM);
  nact.sa_flags = 0;
#ifdef SIG_INTERRUPT
  nact_sa_flags = SA_INTERRUPT; /* don't restart `read(2)' */
#endif
  nact.sa_handler = on_sig_alrm;

  /* return twice */
  if (sigsetjmp (env_alrm, 1 /* save signal mask */) == SIGALRM)
    {
      /* return from on_sig_alrm */
      if (sigprocmask (0, NULL, &oset) == -1)
        {
          /* SIGALRM should be added */
          assert (sigismember (&oset, SIGALRM));
        }
      errno = ETIMEDOUT;
      return -1;
    }
  can_jump = 1;

  if (timeout > 0)
    {
      if (sigaction (SIGALRM, &nact, NULL) == -1)
        {
          return -1;
        }
      /* alarm only catching SIGALRM */
      alarm (timeout);
    }

  return read (fd, buf, nbyte);
}

void
on_sig_alrm (int signo)
{
  if (signo == SIGALRM)
    {
      if (can_jump)
        {
          can_jump = 0;
          siglongjmp (env_alrm, signo);
        }
    }
}
