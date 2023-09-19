#include "_signal_.h"


/*
 * Extends `read(2)' to support `timeout'.
 *
 * 1. Same as `read(2)' excepts
 *
 * 2. `errno(3)' be set to `EINTR' if the `timeout' expires.
 *
 */

ssize_t read1 (int, void *, size_t, int timeout);

static void on_sig_alrm (int signo);

static sigjmp_buf env_alrm;

ssize_t
read1 (int fd, void *buf, size_t count, int timeout)
{
  struct sigaction nact;

  alarm (0);

  sigfillset (&nact.sa_mask);
  sigdelset (&nact.sa_mask, SIGALRM);
  nact.sa_flags = 0;
  nact.sa_handler = on_sig_alrm;

  if (sigsetjmp (env_alrm, 1) == SIGALRM)
    {
      errno = EINTR;
      return -1;
    }

  if (timeout > 0)
    {
      if (sigaction (SIGALRM, &nact, NULL) == -1)
        {
          return -1;
        }
      alarm (timeout);
    }

  return read (fd, buf, count);
}

void
on_sig_alrm (int signo)
{
  if (signo == SIGALRM)
    {
      siglongjmp (env_alrm, signo);
    }
}
