#include "_stdio_.h"

static void  test_wide(int);

int
main(int argc, char *argv[])
{
  int  mode;

  if (argc < 2)
    {
      mode = 0;
    }
  else
    {
      mode = atoi(argv[1]);
    }

  test_wide(mode);

  exit(EXIT_SUCCESS);
}

void
test_wide(int mode)
{
  int     rc;
  char   *ss[]  =  {_str_(stdin), _str_(stdout), _str_(stderr), NULL};
  FILE   *fs[]  =  {stdin, stdout, stderr, NULL};
  char  **ps;
  FILE  **pf;

  for (ps = ss, pf = fs; *ps && *pf; ps++, pf++)
    {
      rc = fwide(*pf, mode);
      printf("fwide(%2d): %6s (%s)\n", mode, *ps,
             rc > 0 ? "wide-oriented"
             : rc == 0 ? "no-oriented" : "byte-oriented");
    }
}
