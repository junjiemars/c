#include "_term_.h"
#include <signal.h>

/*
 * Watching SIGWINCH signal.
 *
 * History: termcap -> terminfo -> curses -> ncurses
 *
 */


static void pr_wsize(int);
static void on_sig_winch(int);

static int  fd  =  STDIN_FILENO;

int
main(void)
{

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

  pr_wsize(fd);


#if (_PAUSE_)
  for (;;)
    {
      /* press Ctrl-C or Ctrl-\ to quit */
      pause();
    }

#endif  /* _PAUSE */


  exit(EXIT_SUCCESS);

}

void
pr_wsize(int fd)
{
  struct winsize  wsz;

  if (ioctl(fd, TIOCGWINSZ, (char *) &wsz) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("%d rows, %d columns\n", wsz.ws_row, wsz.ws_col);

}


void
on_sig_winch(int signo)
{
  if (signo == SIGWINCH)
    {
      printf("on %s...\n", _str_(SIGWINCH));

      pr_wsize(fd);
    }
}
