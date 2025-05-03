#include "_io_.h"
#include <getopt.h>

int
main (int argc, char *argv[])
{
  int ch;
  int opt_aflag, opt_mflag;

  opt_aflag = opt_mflag = 0;

  while ((ch = getopt (argc, argv, "am")) != -1)
    {
      switch (ch)
        {
        case 'a':
          opt_aflag = 1;
        case 'm':
          opt_mflag = 1;
        }
    }
  argc -= optind;
  argv += optind;

  if (opt_aflag == 0 && opt_mflag == 0)
    {
      opt_aflag = opt_mflag = 1;
    }


  return 0;
}
