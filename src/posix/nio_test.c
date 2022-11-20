#include "nio.h"
#include <stdlib.h>


static void test_getline(FILE *);
static void test_fileno(void);
static void test_fdopen(void);
static void test_dirname(void);
static void test_basename(void);


int
main(int argc, char **argv)
{
  FILE  *file;

  if (argc > 1)
    {
      if ((file = fopen(argv[1], "r")) == NULL)
        {
          perror(NULL);
        }
    }
  else
    {
      file = stdin;
    }

  test_getline(file);

  test_fileno();
  test_fdopen();

  test_dirname();
  test_basename();

  return 0;
}


void
test_getline(FILE *file)
{
  if (file == NULL)
    {
      printf("%s: invalid `file' argument\n", __FUNCTION__);
    }

#if !(NM_HAVE_GETDELIM)
  printf("%s: no `getdelim' found\n", __FUNCTION__);

#else

  extern ssize_t getdelim(char ** restrict lineptr, size_t * restrict n,
                          int delimiter, FILE * restrict stream);

  char     *line;
  size_t    linecap;
  ssize_t   linelen;

  line = NULL;
  linecap = 0;
  while ((linelen = getline(&line, &linecap, file)) > 0)
    {
      fprintf(stdout, "%s", line);
    }

  if (ferror(file))
    {
      perror(NULL);
    }

  free(line);
  fclose(file);

#endif  /* getdelim */

}


void
test_fileno(void)
{
#if !(NM_HAVE_FILENO)
  printf("%s: no `fileno' found\n", __FUNCTION__);

#else

  printf("stdin=%d, stdout=%d, stderr=%d\n",
         fileno(stdin),
         fileno(stdout),
         fileno(stderr));

#endif  /* fileno */

}


void
test_fdopen(void)
{
#if !(NM_HAVE_FDOPEN)
  printf("%s: no `fdopen' found\n", __FUNCTION__);

#else

  FILE *f;
  f = fdopen(0, "r");
  fclose(f);

#endif  /* fdopen */
}

void
test_dirname(void)
{
#if !((NM_HAVE_DIRNAME) || (NM_HAVE_DIRNAME_GETFULLPATHNAME))
  printf("%s: no `dirname' found\n", __FUNCTION__);

#else

#  if (NM_HAVE_DIRNAME)
#    include <libgen.h>
#  endif

#  if (MSVC)
#    pragma warning(disable: 4210)
#  endif

  extern char  *dirname(char *);

  char s[] = "/a/b/c";
  char *n = dirname(s);
  printf("dirname(\"%s\") = \"%s\"\n", s, n);

#endif  /* dirname */

}

void
test_basename(void)
{
#if !((NM_HAVE_BASENAME) || (NM_HAVE_BASENAME_GETFULLPATHNAME))
  printf("%s: no `basename' found\n", __FUNCTION__);

#else

#  if (NM_HAVE_BASENAME)
#    include <libgen.h>
#  endif

#  if (MSVC)
#    pragma warning(disable: 4210)
#  endif

  extern char  *basename(char *);

  char s[] = "/a/b/c";
  char *b = basename(s);
  printf("basename(\"%s\") = \"%s\"\n", s, b);

#endif  /* basename */

}
