#include "_io_.h"


int
main(int argc, char *argv[])
{
  int  ch;

	_unused_(argc);
	_unused_(argv);

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
