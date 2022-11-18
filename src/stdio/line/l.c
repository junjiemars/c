#include "_stdio_.h"
#include <nint.h>


#define LINE_LEN_MAX  (sizeof(void*))

static void test_getline(const char *where);
static void test_fgets(const char *where);

void
test_getline(const char *where)
{
	FILE     *file;
	char     *line  =  0;
	size_t    n;
	ssize_t   len;

  file = fopen(where, "r");
	if (!file)
    {
      perror(0);
      return;
    }

  n = LINE_LEN_MAX;
  line = malloc(n);
  if (!line)
    {
      perror(0);
      return;
    }

	while ((len = getline(&line, &n, file)) > 0)
    {
      fwrite(line, len, 1, stdout);
    }
  if (ferror(file))
    {
      perror(0);
    }

  fclose(file);
  free(line);
}

void
test_fgets(const char *where)
{
	FILE  *file;
	char  *line  =  0;
	int    n;
	char  *s     =  0;

  file = fopen(where, "r");
	if (!file)
    {
      perror(0);
      return;
    }

  n = LINE_LEN_MAX;
  line = malloc(n);
  if (!line)
    {
      perror(0);
      return;
    }

	while ((s = fgets(line, n, file)) != NULL)
    {
      printf("%s", s);
    }
  if (ferror(file))
    {
      perror(0);
    }

  fclose(file);
  free(line);
}


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      printf("where the file located?\n");
      return 0;
    }

  test_getline(argv[1]);
  test_fgets(argv[1]);

	return 0;
}


/* eof */
