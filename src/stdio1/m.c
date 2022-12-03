#include "_stdio1_.h"


extern FILE  *stdin, *stdout, *stderr;


__attribute__((unused)) static void test_u(int argc, char *argv[]);
__attribute__((unused)) static void test_c(int argc, char *argv[]);
__attribute__((unused)) static void test_b(int argc, char *argv[]);
__attribute__((unused)) static void test_p(int argc, char *argv[]);
__attribute__((unused)) static void test_v(int argc, char *argv[]);

int
main(int argc, char *argv[])
{
  test_u(argc, argv);
  test_c(argc, argv);
  test_b(argc, argv);
  test_p(argc, argv);
  test_v(argc, argv);

  return 0;
}


void
test_u(int argc, char *argv[])
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

  fputc(UCHAR_MAX, out);
  fputc('\n', out);

  fputc('A', stderr);
  fputc('\n', stderr);

  fclose(in);
  fclose(out);
  fclose(stderr);
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

void
test_p(int argc, char *argv[])
{
  for (int i = 0; i < argc; i++)
    {
      fprintf(stdout, "argv[%d] = %s\n", i, argv[i]);
    }
}

void
test_v(int argc, char *argv[])
{
  char  buf[BUFSIZ];

  if (setvbuf(stdout, buf, _IOFBF, BUFSIZ))
    {
      fprintf(stderr, "%s\n", strerror(errno));
      return;
    }

  for (int i = 0; i < argc; i++)
    {
      fprintf(stdout, "argv[%d] = %s\n", i, argv[i]);
    }
}
