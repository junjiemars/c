#include "_io_.h"

int
main(void)
{
  int c;

  while ((c = fgetc(stdin)) != EOF)
    {
      if (fputc(c, stdout) == EOF)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  if (ferror(stdin))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
