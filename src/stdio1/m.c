#include "_stdio1_.h"


extern FILE  *stdin, *stdout, *stderr;


__attribute__((unused)) static void test_c(FILE *, FILE *);
static void test_b(FILE *, FILE *);

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

  /* test_c(in, out); */
  test_b(in, out);

  return 0;
}


void
test_c(FILE *in, FILE *out)
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

void
test_b(FILE *in, FILE *out)
{
  int   r, w;
  char  buf[BUFSIZ];

  while ((r = fread(buf, sizeof(*buf), sizeof(buf), in)) > 0)
    {
      if ((w = fwrite(buf, sizeof(*buf), r, out)) != r)
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
