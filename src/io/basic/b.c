#include "_io_.h"
#include <stdio.h>

int
main(int argc, char *argv[])
{
	_unused_(argc);
	_unused_(argv);

	int ch;
	while (EOF != (ch = fgetc(stdin)))
    {
      fputc(ch, stdout);
    }
	if (ferror(stdin))
    {
      perror("!panic");
      return 1;
    }
  if (feof(stdin))
    {
      fprintf(stdout, "#%s\n", "end of file");
    }

	return 0;
}
