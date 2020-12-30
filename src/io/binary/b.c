#include <_io_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef MSVC
#  include <windows.h>
#  include <tchar.h>
#  define PATH_MAX MAX_PATH
#else
#  ifdef LINUX
#    include <linux/limits.h>
#  else
#    include <limits.h>
#  endif
#  include <libgen.h>
#endif

#define NAME_SIZE 16

typedef struct rect_s
{
  char name[NAME_SIZE];
  int width;
  int height;
} rect_s;

char *dirname(char *path);
void out(const rect_s *rect, const char *where);
void in(rect_s *rect, const char *where);


#ifdef MSVC
char*
dirname(char *path)
{
  static TCHAR d[PATH_MAX + 1], *b;
  if (0 == GetFullPathName(path, _countof(d), d, &b))
    {
      return 0;
    }
  b[-1] = 0; /* remove '/basename' part */
  return d;
}
#endif /* end of MSVC */

void
out(const rect_s *rect, const char *where)
{
  FILE *f = fopen(where, "w");
  if (!f)
    {
      perror(where);
      return;
    }

  size_t len = fwrite((char*)rect, 1, sizeof(rect_s), f);

  if (ferror(f))
    {
      perror(where);
      clearerr(f);
      goto clean_exit;
    }

  if (sizeof(rect_s) != len)
    {
      fprintf(stderr, "!panic: write %zu bytes, but expect %zu bytes\n",
              len, sizeof(rect_s));
    }
  
 clean_exit:
  fclose(f);
}

void
in(rect_s *rect, const char *where)
{
  FILE *f = fopen(where, "r");
  if (!f)
    {
      perror(where);
      return;
    }

  size_t len = fread((char*)rect, 1, sizeof(rect_s), f);

  if (ferror(f))
    {
      perror(where);
      clearerr(f);
      goto clean_exit;
    }

  if (sizeof(rect_s) != len)
    {
      fprintf(stderr, "!panic: read %zu bytes, but expect %zu bytes\n",
              len, sizeof(rect_s));
      goto clean_exit;
    }

  fprintf(stdout,"\
rect_s:{\n\
  name: \"%s\",\n\
  width:  0x%08x,\n\
  height: 0x%08x\n\
}\n", rect->name, rect->width, rect->height);

 clean_exit:
  fclose(f);
}

int
main(int argc, char **argv)
{
  char filename[PATH_MAX];
  rect_s rect;
  memset(&rect, 0, sizeof(rect));
  char *pathname = dirname(argv[0]);
  strcpy(filename, pathname);
  strcat(filename, "/.rect_s");

  if (argc < 4)
    {
      /* read from binary file */
      in(&rect, filename);
    }
  else
    {
      /* write to binary file */
      strncpy(rect.name, argv[1], NAME_SIZE);
      rect.width = (int)strtol(argv[2], 0, 16);
      rect.height = (int)strtol(argv[3], 0, 16);

      out(&rect, filename);
    }

  return 0;
}
