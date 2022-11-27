#include "_stdio1_.h"


extern FILE  *stdin, *stdout, *stderr;


static void test_c(int argc, char *argv[]);
static void test_b(int argc, char *argv[]);

int
main(int argc, char *argv[])
{
  test_c(argc, argv);
  test_b(argc, argv);

  return 0;
}


void
test_c(int argc, char *argv[])
{
  FILE  *in, *out;
  int    r;

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

  fclose(in);
  fclose(out);
}


void
test_b(int argc, char *argv[])
{
  FILE  *in, *out;
  int    r, w;
  char   buf[BUFSIZ];

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

  while ((r = fread(buf, sizeof(*buf), _nof_(buf), in)) > 0)
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

  fclose(in);
  fclose(out);
}
