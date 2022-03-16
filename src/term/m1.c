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
  struct termios  oterm, nterm;

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

  rc = tcgetattr(STDIN_FILENO, &oterm);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  oterm.c_cc[VINTR] = vdisable;
  oterm.c_cc[VEOF] = '';         /* 2 */

  rc = tcsetattr(STDIN_FILENO, TCSANOW, (const struct termios *) &oterm);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  rc = tcgetattr(STDIN_FILENO, &nterm);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  assert(memcpy(&oterm, &nterm, sizeof(struct termios)));

  exit(EXIT_SUCCESS);

}
