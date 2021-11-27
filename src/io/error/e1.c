#include <_io_.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int
main(int argc, char **argv)
{
  char  *path;
  FILE  *file;

  if (argc < 2)
    {
      fprintf(stderr, "where the where.c locate?\n");
      return 0;
    }
  path = argv[1];

  file = fopen(path, "r");
  if (0 == file)
    {
      int errnum = errno;
      fprintf(stdout, "!panic1: %s\n", strerror(errnum));
      perror("!panic2");
    }
  else
    {
      int  ch;
      fprintf(stdout, "%s found\n", path);

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
