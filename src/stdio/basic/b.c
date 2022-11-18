#include "_stdio_.h"

/* debugging: C-d */

int
main(void)
{
  int  ch;

  while (EOF != (ch = fgetc(stdin)))
    {
      fputc(ch, stdout);
    }

  if (ferror(stdin))
    {
      perror("!stdin");
      exit(EXIT_FAILURE);
    }

  if (feof(stdin))
    {
      fprintf(stdout, "/* %s */.\n", "end of file");
    }

  exit(EXIT_SUCCESS);
}
