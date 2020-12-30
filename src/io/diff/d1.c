#include <_io_.h>
#include <stdio.h>
#include <string.h>

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
#endif

#define MAX_LINE PATH_MAX

void diff(const char *src, const char *dst);

void diff(const char *src, const char *dst)
{
  FILE *fsrc = 0, *fdst = 0;
  char lsrc[MAX_LINE], ldst[MAX_LINE];
  char *eof_src = 0, *eof_dst = 0;
  
  fsrc = fopen(src, "r");
  if (!fsrc)
    {
      perror(NULL);
      goto clean_exit;
    }
  fdst = fopen(dst, "r");
  if (!fdst)
    {
      perror(NULL);
      goto clean_exit;
    }
      
  fprintf(stdout, "--- %s\n", src);
  fprintf(stdout, "+++ %s\n", dst);

  do
    {
      if (!feof(fsrc))
        {
          eof_src = fgets(lsrc, MAX_LINE, fsrc);
          if (ferror(fsrc))
            {
              perror(src);
            }
        }
      if (!feof(fdst))
        {
          eof_dst = fgets(ldst, MAX_LINE, fdst);
          if (ferror(fdst))
            {
              perror(dst);
            }
        }

      if (NULL == eof_src && NULL == eof_dst)
        {
          goto clean_exit;
        }

      if (eof_src != NULL && eof_dst != NULL)
        {
          if (0 == strncmp(lsrc, ldst, MAX_LINE))
            {
              fprintf(stdout, " %s", lsrc);
            }
          else
            {
              fprintf(stdout, "-%s", lsrc);
              fprintf(stdout, "+%s", ldst);
            }
          continue;
        }
      if (eof_src == NULL)
        {
          fprintf(stdout, "+%s", ldst);
        }
      if (eof_dst == NULL)
        {
          fprintf(stdout, "-%s", lsrc);
        }
    } while (1);

 clean_exit:
  if (fsrc)
    {
      fclose(fsrc);
    }
  if (fdst)
    {
      fclose(fdst);
    }
}

int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      fprintf(stderr, "please, input src and dst file!\n");
      return 1;
    }

  char src[PATH_MAX], dst[PATH_MAX];
  strncpy(src, argv[1], PATH_MAX);
  strncpy(dst, argv[2], PATH_MAX);
  
  diff(src, dst);

  return 0;
}
