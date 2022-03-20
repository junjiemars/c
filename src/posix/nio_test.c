#include "ndef.h"
#include "nio.h"
#include "ndef.h"
#include "nstr.h"
#include <stdlib.h>

static void test_getline(const char *where);

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

int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      printf("!need a file to read\n");
      return 0;
    }
  test_getline(argv[1]);

  return 0;
}
