#include "_term_.h"
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CBREAK_LFLAG (ECHO | ICANON)

#define RAW_LFLAG (ECHO | ICANON | IEXTEN | ISIG)
#define RAW_IFLAG (BRKINT | ICRNL | INPCK | ISTRIP | IXON)
#define RAW_CFLAG (CSIZE | PARENB)
#define RAW_OFLAG (OPOST)

static void on_sig (int signo);
static void on_exit (void);

static int tty_cbreak (int fd);
static int tty_raw (int fd);
static int tty_reset (int fd);

static int ttyfd = -1;
static struct termios term_saved;
static enum { RESET, RAW, CBREAK } ttystate = RESET;

int
main (void)
{
  int rc;
  char c;
  ssize_t n;

  atexit (on_exit);

  /* trap SIGINT, SIGQUIT and SIGTERM */
  if (signal (SIGINT, on_sig) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  if (signal (SIGQUIT, on_sig) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  if (signal (SIGTERM, on_sig) == SIG_ERR)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  /* switch to raw mode */
  rc = tty_raw (STDIN_FILENO);
  if (rc == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("\nEnter raw mode, terminate with DELETE or Backspace\n");

  while ((n = read (STDIN_FILENO, &c, 1)) == 1)
    {
      if ((c &= 255) == 0177)
        {
          break;
        }
      printf ("0x%x\n", c);
    }

  /* restore */
  if (tty_reset (STDIN_FILENO) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  if (n <= 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  /* switch to cbreak mode */
  rc = tty_cbreak (STDIN_FILENO);
  if (rc == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("\nEnter cbreak mode, terminate with SIGINT (ctrl-c)\n");

  while ((n = read (STDIN_FILENO, &c, 1)) == 1)
    {
      c &= 255;
      printf ("0x%x\n", c);
    }

  /* restore */
  if (tty_reset (STDIN_FILENO) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  if (n <= 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  return 0;
}

void
on_sig (int __attribute__ ((unused)) signo)
{
  tty_reset (STDIN_FILENO);
  exit (EXIT_SUCCESS);
}

int
tty_cbreak (int fd)
{
  int err;
  struct termios ts;

  if (ttystate != RESET)
    {
      errno = EINVAL;
      return -1;
    }

  if (tcgetattr (fd, &ts) == -1)
    {
      return -1;
    }
  term_saved = ts;

  ts.c_lflag &= ~CBREAK_LFLAG;
  ts.c_cc[VMIN] = 1;
  ts.c_cc[VTIME] = 0;
  if (tcsetattr (fd, TCSAFLUSH, &ts))
    {
      return -1;
    }

  if (tcgetattr (fd, &ts) == -1)
    {
      err = errno;
      tcsetattr (fd, TCSAFLUSH, &term_saved);
      errno = err;
      return -1;
    }

  if ((ts.c_lflag & CBREAK_LFLAG) || ts.c_cc[VMIN] != 1 || ts.c_cc[VTIME] != 0)
    {
      tcsetattr (fd, TCSAFLUSH, &term_saved);
      errno = EINVAL;
      return -1;
    }

  ttystate = CBREAK;
  ttyfd = fd;
  return 0;
}

int
tty_raw (int fd)
{
  int rc;
  int err;
  struct termios ts;

  if (ttystate != RESET)
    {
      errno = EINVAL;
      return -1;
    }

  rc = tcgetattr (fd, &ts);
  if (rc == -1)
    {
      return -1;
    }
  term_saved = ts;

  ts.c_lflag &= ~RAW_LFLAG;
  ts.c_iflag &= ~RAW_IFLAG;
  ts.c_cflag &= ~RAW_CFLAG;
  ts.c_oflag &= ~RAW_OFLAG;

  ts.c_cc[VMIN] = 1;
  ts.c_cc[VTIME] = 0;

  rc = tcsetattr (fd, TCSAFLUSH, &ts);
  if (rc == -1)
    {
      return -1;
    }

  rc = tcgetattr (fd, &ts);
  if (rc == -1)
    {
      err = errno;
      tcsetattr (fd, TCSAFLUSH, &term_saved);
      errno = err;
      return -1;
    }

  if ((ts.c_lflag & RAW_LFLAG) || (ts.c_iflag & RAW_IFLAG)
      || (ts.c_cflag & RAW_CFLAG) || (ts.c_oflag & RAW_OFLAG)
      || (ts.c_cc[VMIN] != 1 || ts.c_cc[VTIME] != 0))
    {
      tcsetattr (fd, TCSAFLUSH, &term_saved);
      errno = EINVAL;
      return -1;
    }

  ttystate = RAW;
  ttyfd = fd;
  return 0;
}

int
tty_reset (int fd)
{
  if (ttystate == RESET)
    {
      return 0;
    }

  if (tcsetattr (fd, TCSAFLUSH, &term_saved) == -1)
    {
      return -1;
    }

  ttystate = RESET;
  return 0;
}

void
on_exit ()
{
  if (ttyfd >= 0)
    {
      tty_reset (ttyfd);
    }
}
