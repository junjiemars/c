#include "_term_.h"
#include <termios.h>

/*
 * 1. disable INTR.
 * 2. map EOF to Ctrl-B.
 *
 */

int
main(void)
{
  int             rc;
  long            vdisable;
  struct termios  term;

  rc = isatty(STDIN_FILENO);
  if (rc == 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  vdisable = fpathconf(STDIN_FILENO, _PC_VDISABLE);
  if (vdisable == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  rc = tcgetattr(STDIN_FILENO, &term);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  term.c_cc[VINTR] = vdisable;
  term.c_cc[VEOF] = '';         /* 2 */

  rc = tcsetattr(STDIN_FILENO, TCSANOW, (const struct termios *) &term);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);

}
