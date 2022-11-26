#include "_stdio_.h"

static char  ibuf[BUFSIZ];
static char  obuf[BUFSIZ];

static int mode(const char *);

int
main(int argc, char *argv[])
{
  int  imode  =  _IONBF;
  int  omode  =  _IONBF;

  if (argc > 1)
    {
      imode = mode(argv[1]);
    }
  else if (argc > 2)
    {
      omode = mode(argv[2]);
    }

  if (setvbuf(stdin, ibuf, imode, BUFSIZ))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (setvbuf(stdout, obuf, omode, BUFSIZ))
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }




  exit(EXIT_SUCCESS);
}

int
mode(const char *s)
{
  if (strcmp(s, _str_(_IOFBF)) == 0)
    {
      return _IOFBF;
    }
  else if (strcmp(s, _str_(_IOLBF)) == 0)
    {
      return _IOLBF;
    }
  else
    {
      return _IONBF;
    }
}
