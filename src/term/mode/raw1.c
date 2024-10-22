#include "_term_.h"
#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void on_sig (int signo);
static void on_atexit (void);

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

  atexit (on_atexit);

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
      printf ("%o\n", c);
    }

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
      printf ("%o\n", c);
    }
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
on_sig (int signo)
{
  printf ("on signal: %d\n", signo);
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

  ts.c_lflag &= ~(ECHO | ICANON);
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

  if ((ts.c_lflag & (ECHO | ICANON)) || ts.c_cc[VMIN] != 1
      || ts.c_cc[VTIME] != 0)
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

  ts.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  ts.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  ts.c_cflag &= ~(CSIZE | PARENB);
  ts.c_oflag &= ~(OPOST);

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

  if ((ts.c_lflag & (ECHO | ICANON | IEXTEN | ISIG))
      || (ts.c_iflag & (BRKINT | ICRNL | INPCK | ISTRIP | IXON))
      || (ts.c_cflag & (CSIZE | PARENB)) || (ts.c_oflag & OPOST)
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
on_atexit ()
{
  if (ttyfd >= 0)
    {
      tty_reset (ttyfd);
    }
}
