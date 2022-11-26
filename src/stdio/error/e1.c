#include "_stdio_.h"


int
main(int argc, char **argv)
{
  FILE  *file;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <pathname>\n");
      return 0;
    }

  file = fopen(argv[1], "r");
  if (0 == file)
    {
      perror(NULL);
    }
  else
    {
      int  ch;
      fprintf(stdout, "%s found\n", argv[1]);

      while (EOF != (ch = fgetc(file)))
        {
          fputc(ch, stdout);
        }

      if (ferror(file))
        {
          perror(NULL);
          clearerr(file);
        }

      if (feof(file))
        {
          fprintf(stdout, "end of %s\n", argv[1]);
        }

      fclose(file);
    }

  return 0;
}
