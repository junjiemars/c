#include "_lang_.h"

static void  test_open_file(const char*);
static void  test_sqrt(double);

int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      printf("input a filename\n");
      return 1;
    }

  test_open_file(argv[1]);
  test_sqrt(-1 * argc);

  return 0;
}


void
test_open_file(const char *filename)
{
  FILE *out = fopen(filename, "r");
  if (out)
    {
      fprintf(stdout, "#open %s success\n", filename);
      goto clean_exit;
    }

  int e = errno;
  if (e)
    {
      perror("!panic");
    }

 clean_exit:
  if (out)
    {
      fclose(out);
    }
}

void
test_sqrt(double x)
{
  double  d    =  sqrt(x);
  int     err  =  errno;

  if (err)
    {
      fprintf(stderr, "!panic: %s\n", strerror(err));
    }
  printf("%f\n", d);
}
