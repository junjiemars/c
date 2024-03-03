#include "_io_.h"

/*
 * user-mode to kenerl mode.
 *
 */

char buffer[2048];
int version = 1;

void copy (int, int);

int
main (int argc, char **argv)
{
  int fdold, fdnew;

  if (argc != 3)
    {
      fprintf (stderr, "usage: <old> <new>\n");
      exit (EXIT_FAILURE);
    }

  if ((fdold = open (argv[1], O_RDONLY)) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  if ((fdnew = open (argv[2], O_WRONLY | O_CREAT, 0666)) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  copy (fdold, fdnew);

  exit (EXIT_SUCCESS);
}

void
copy (int old, int new)
{
  int count;
  while ((count = read (old, buffer, sizeof (buffer))) > 0)
    {
      write (new, buffer, count);
    }
}
