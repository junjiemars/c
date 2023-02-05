#include "_ipc_.h"


extern FILE  *popen(const char*, const char*);
extern int    pclose(FILE *stream);


int
paging(const char *pathname, const char *pager)
{
  char      line[NM_LINE_MAX];
  FILE     *fpin, *fpout;

  if ((fpin = fopen(pathname, "r")) == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if ((fpout = popen(pager, "w")) == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  while (fgets(line, NM_LINE_MAX, fpin) != NULL)
    {
      if (fputs(line, fpout) == EOF)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  if (ferror(fpin))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (pclose(fpout) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  return 0;
}
