#include "defs.h"
#include "ioss.h"

static void test_getline(const char *where);

void
test_getline(const char *where)
{
  char    *buf;
  size_t   n;
  FILE    *f;
  int      rc;

  f = fopen(where, "r");
  if (!f)
    {
      perror(0);
      return;
    }
  
  buf = 0;
  n = 0;
  rc = getline(&buf, &n, f);
  if (rc == EOF)
    {
      perror(0);
      goto clean_exit;
    }
  printf("getline: %s\n", buf);
    
 clean_exit:
  free(buf);
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
