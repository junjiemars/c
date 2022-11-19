#include "_stdio_.h"

int
main(void)
{
  int    c;
  FILE  *in, *out;

  in = fdopen(0, "r");
  if (in == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  out = fdopen(1, "w");
  if (out == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  while ((c = fgetc(in)) != EOF)
    {
      if (fputc(c, out) == EOF)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  exit(EXIT_SUCCESS);
}
