#include "nio.h"
#include <stdlib.h>


static void test_getline(const char *where);
static void test_fileno(void);


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      printf("!need a file to read\n");
      return 0;
    }
  test_getline(argv[1]);

  test_fileno();

  return 0;
}


void
test_getline(const char *where)
{
  char     *line;
  size_t    linecap;
  ssize_t   linelen;
  FILE     *f;

  f = fopen(where, "r");
  if (!f)
    {
      perror(0);
      return;
    }

  line = NULL;
  linecap = 0;
  while ((linelen = getline(&line, &linecap, f)) > 0)
    {
      fprintf(stdout, "%s", line);
    }

  if (ferror(f))
    {
      perror(0);
    }

  free(line);
  fclose(f);
}


void
test_fileno(void)
{
  printf("stdin=%d, stdout=%d, stderr=%d\n",
         fileno(stdin),
         fileno(stdout),
         fileno(stderr));

}
