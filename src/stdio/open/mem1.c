#include <_stdio_.h>

int
main (void)
{
  int n;
  FILE *in;
  char mem[BUFSIZ];
  char buf[16];

  in = fmemopen (mem, BUFSIZ, "w+");
  if (in == NULL)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  n = fprintf (in, "%s\n", "abc");
  assert (n == 4 && "should 4 characters");

  fseek (in, 0, SEEK_SET);
  fread(buf, sizeof (*buf), 3, in);
  assert (strcmp (buf, "abc") == 0 && "should equals abc");

  fclose (in);

  exit (EXIT_SUCCESS);
}
