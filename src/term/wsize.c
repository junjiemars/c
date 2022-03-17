#include "_term_.h"
#include <sys/ioctl.h>

/*
 * Watching SIGWINCH signal.
 *
 */

/* #if (DARWIN) */
/* #  if !defined(SIGWINCH) */
/* #    define SIGWINCH  28 */
/* #  endif */
/* #endif  /\* DARWIN *\/ */

#include <signal.h>


static void pr_wsize(const struct ttysize *ts);
static void on_sig_winch(int signo);

static int  fd  =  STDIN_FILENO;

int
main(void)
{
  int             rc;
  struct ttysize  ts;

  if (isatty(fd) == 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (signal(SIGWINCH, on_sig_winch) == SIG_ERR)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  rc = ioctl(fd, TIOCGWINSZ, &ts);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  pr_wsize(&ts);

  for (;;)
    {
      pause();
    }

  exit(EXIT_SUCCESS);

}

void
pr_wsize(const struct ttysize *ts)
{
  printf("%d rows, %d columns\n", ts->ts_lines, ts->ts_cols);
}


void
on_sig_winch(int signo)
{
  struct ttysize  ts;

  if (signo == SIGWINCH)
    {
      if (ioctl(fd, TIOCGWINSZ, &ts) == -1)
        {
          pr_wsize(&ts);
        }
    }
}
