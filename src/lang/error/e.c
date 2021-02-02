#include <_lang_.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#if (LINUX)
#  if defined(_GNU_SOURCE)
#    undef _GNU_SOURCE
#  endif  /* _GNU_SOURCE */
#  include <errno.h>
#else
#  include <errno.h>
#endif  /* LINUX */

#define BSIZE 512

void
test_open_file(const char *filename) 
{
  FILE *out = fopen(filename, "r");
  if (out)
    {
      fprintf(stderr, "#open %s success\n", filename);
      goto clean_exit;
    }

  int e = errno;
  if (e) 
    {
      char buf[BSIZE];
      snprintf(buf, BSIZE, "!panic, open %s", filename);
      perror(buf);
      
      int r = strerror_r(e, buf, sizeof(buf));
      if (0 == r) 
        {
          fprintf(stderr, "!panic, strerror_r, \"%s\"\n", buf);
        }
      else 
        {
          fprintf(stderr, "#!panic, strerror, \"%s\"\n", strerror(r));
        }
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
  double d = sqrt(x);
  printf("%f\n", d);
}

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
