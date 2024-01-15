#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 4

int
main (int argc, char **argv)
{
  unsigned char buf[BUFSIZE];
  FILE *fin;

  if (argc < 2)
    {
      fprintf (stdout, "usage: <bin-path>\n");
      exit (EXIT_FAILURE);
    }

  if ((fin = fopen (argv[1], "rb")) == NULL)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  pause ();

  if ((fread (buf, sizeof (*buf), BUFSIZE, fin)) != BUFSIZE)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("%#04x%02x%02x%02x\n", buf[0], buf[1], buf[2], buf[3]);

  return 0;
}
