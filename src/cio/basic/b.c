#include "_cio_.h"

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
      return 1;
    }
  if (feof(stdin))
    {
      fprintf(stdout, "/* %s */\n", "end of file");
    }

  return 0;
}
