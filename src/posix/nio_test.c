#include "nio.h"
#include <stdlib.h>


extern ssize_t getdelim(char ** restrict lineptr, size_t * restrict n,
                        int delimiter, FILE * restrict stream);


static void test_getline(const char *where);
static void test_fileno(void);
static void test_fdopen(void);
static void test_dirname(void);
static void test_basename(void);


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      printf("usage: %s <file>\n", argv[0]);
      return 0;
    }
  test_getline(argv[1]);

  test_fileno();
  test_fdopen();

  test_dirname();
  test_basename();

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
#if (NM_HAVE_FILENO)
  printf("stdin=%d, stdout=%d, stderr=%d\n",
         fileno(stdin),
         fileno(stdout),
         fileno(stderr));

#endif  /* fileno */
}


void
test_fdopen(void)
{
#if (NM_HAVE_FDOPEN)
  FILE *f;
  f = fdopen(0, "r");
  fclose(f);

#endif  /* fdopen */
}

void
test_dirname(void)
{

#if (NM_HAVE_DIRNAME) || (NM_HAVE_DIRNAME_GETFULLPATHNAME)
#  if (NM_HAVE_DIRNAME)
#    include <libgen.h>
#  endif

  extern char *dirname(char *);

  char s[] = "/a/b/c";
  char *n = dirname(s);
  printf("dirname(\"%s\") = %s\n", s, n);

#endif  /* dirname */
}

void
test_basename(void)
{
#if (NM_HAVE_BASENAME)
#  include <libgen.h>

  extern char *basename(char *);

  char s[] = "/a/b/c";
  char *b = basename(s);
  printf("basename(\"%s\") = %s\n", s, b);

#endif  /* basename */
}
