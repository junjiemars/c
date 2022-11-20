#include "_stdio_.h"


int
main(void)
{
  char   *ss[]  =  {_str_(stdin), _str_(stdout), _str_(stderr), NULL};
  FILE   *fs[]  =  {stdin, stdout, stderr, NULL};
  char  **ps;
  FILE  **pf;

  for (ps = ss, pf = fs; *ps && *pf; ps++, pf++)
    {
      int  mode;

      mode = fwide(*pf, 0);
      printf("%s: %s\n", *ps,
             mode > 0 ? "wide oriented"
             : mode == 0 ? "no oriented" : "byte oriented");
    }

  exit(EXIT_SUCCESS);
}
