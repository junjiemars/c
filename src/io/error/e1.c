#include <_io_.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "where the where.c find locate?\n");
      return 0;
    }

	char *path = argv[1];
	FILE *file = fopen(path, "r");
	if (0 == file)
    {
      int errnum = errno;
      fprintf(stdout, "!panic1: %s\n", strerror(errnum));
      perror("!panic2");
    }
  else
    {
      fprintf(stdout, "%s found\n", path);
      int ch;
      while (EOF != (ch = fgetc(file)))
        {
          fputc(ch, stdout);
        }
      if (ferror(file))
        {
          perror(NULL);
          clearerr(file);
        }
      fclose(file);
    }

	return 0;
}
