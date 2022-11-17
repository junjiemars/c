#include "_data_.h"


#define BUF_SIZE  NAME_MAX

static char  buf[BUF_SIZE];


int
main(__attribute__((unused)) int argc, __attribute__((unused)) char *argv[])
{
  if (argc > 1)
    {
#if (NM_HAVE_SETLOGIN)
      if (setlogin(argv[1]) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
#else
      printf("!panic: setlogin unsupported, ignore '%s'\n", argv[1]);

#endif  /* setlogin */

    }


  if (getlogin_r(buf, BUF_SIZE) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("LOGNAME=%s\n", buf);

  exit(EXIT_SUCCESS);
}
