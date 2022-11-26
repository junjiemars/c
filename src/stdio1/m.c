#include "_stdio1_.h"


extern FILE  *stdin, *stdout, *stderr;


static void test(FILE *);

int
main(int argc, char *argv[])
{
  FILE  *ss  =  NULL;

  if (argc > 1)
    {
      ss = fopen(argv[1], "r");
    }
  else
    {
      ss = stdin;
    }

  test(ss);

  return 0;
}


void
test(FILE *ss)
{
  int  r;

  while ((r = fgetc(ss)) != EOF)
    {
      if (fputc(r, stdout) == EOF)
        {
          if (ferror(stdout))
            {
              break;
            }
        }
    }

  if (ferror(ss))
    {
    }
  if (feof(ss))
    {
    }

  fclose(ss);
}
