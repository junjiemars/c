#include "_stdio_.h"

/*
 * 1. stdin can be closed, then no error occurred when read.
 *
 */

static void close_stdin(void);

int
main(void)
{
  close_stdin();
  exit(EXIT_SUCCESS);
}

void
close_stdin(void)
{
  int  c;

   if (fclose(stdin) == EOF)
    {
      perror(NULL);
    }

  while ((c = fgetc(stdin)) != EOF)
    {
      if (fputc(c, stdout))
        {
          perror(NULL);
        }
    }
}
