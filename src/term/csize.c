#include "_term_.h"

/*
 * set character-size to 8 bits/byte.
 *
 */

int
main (void)
{
  int rc;
  struct termios oterm, nterm;

  rc = tcgetattr (STDIN_FILENO, &oterm);
  if (rc == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  switch (oterm.c_cflag & CSIZE)
    {
    case CS5:
      printf ("5 bits/byte\n");
      break;
    case CS6:
      printf ("6 bits/byte\n");
      break;
    case CS7:
      printf ("7 bits/byte\n");
      break;
    case CS8:
      printf ("8 bits/byte\n");
      break;
    default:
      printf ("(unknown bits/byte)\n");
      break;
    }

  oterm.c_cflag &= ~CSIZE;
  oterm.c_cflag |= CS8;

  rc = tcsetattr (STDIN_FILENO, TCSANOW, (const struct termios *)&oterm);
  if (rc == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  rc = tcgetattr (STDIN_FILENO, &nterm);
  if (rc == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  assert (memcpy (&oterm, &nterm, sizeof (struct termios)));

  exit (EXIT_SUCCESS);
}
