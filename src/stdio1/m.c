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
test(FILE *in)
{
  int  r;

  while ((r = fgetc(in)) != EOF)
    {
      if (fputc(r, stdout) == EOF)
        {
          if (ferror(stdout))
            {
              char  *s  =  strerror(stdout->err);
              fwrite(s, sizeof(*s), strlen(s), stderr);
              break;
            }
        }
    }

  if (ferror(in))
    {
      char  *s  =  strerror(in->err);
      fwrite(s, sizeof(*s), strlen(s), stderr);
    }

  fclose(in);
}
