#include "_stdio1_.h"


extern FILE  *stdin, *stdout, *stderr;


static void test(FILE *, FILE *);

int
main(int argc, char *argv[])
{
  FILE  *in, *out;

  if (argc > 2)
    {
      in = fopen(argv[1], "r");
      out = fopen(argv[2], "w");
    }
  else if (argc > 1)
    {
      in = fopen(argv[1], "r");
      out = stdout;
    }
  else
    {
      in = stdin;
      out = stdout;
    }

  test(in, out);

  return 0;
}


void
test(FILE *in, FILE *out)
{
  int  r;

  while ((r = fgetc(in)) != EOF)
    {
      if (fputc(r, out) == EOF)
        {
          if (ferror(out))
            {
              char  *s  =  strerror(out->err);
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

  fclose(out);
  fclose(in);
}
