#include "_term_.h"
#include <errno.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>

/*
 * Watching SIGWINCH signal.
 *
 * History: termcap -> terminfo -> curses -> ncurses
 *
 */

static void pr_wsize (int);
static void on_sig_winch (int);

static int fd = STDIN_FILENO;
static int paused = 0;

int
main (int argc, char **argv)
{
  if (argc > 1)
    {
      sscanf (argv[1], "%d", &paused);
    }

  if (isatty (fd) == 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

#if (NM_HAVE_TTY_NAME_R)
  char ss[_POSIX_PATH_MAX];
  if (ttyname_r (fd, ss, _POSIX_PATH_MAX) == 0)
    {
      printf ("fd %d %s\n", fd, ss);
    }
#else
  char *ss;
  if ((ss = ttyname (fd)) != NULL)
    {
      printf ("fd %d %s\n", fd, ss);
    }
#endif

  if (signal (SIGWINCH, on_sig_winch) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  signal (SIGINT, on_sig_winch);

  pr_wsize (fd);

  if (paused)
    {
      for (;;)
        {
          /* press Ctrl-C or Ctrl-\ to quit */
          pause ();
        }
    }

  exit (EXIT_SUCCESS);
}

void
pr_wsize (int fd)
{
  struct winsize wsz;

  if (ioctl (fd, TIOCGWINSZ, (char *)&wsz) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  printf ("%d rows, %d columns\n", wsz.ws_row, wsz.ws_col);
}

void
on_sig_winch (int signo)
{
  if (signo == SIGWINCH)
    {
      pr_wsize (fd);
    }
  else
    {
      exit (0);
    }
}
