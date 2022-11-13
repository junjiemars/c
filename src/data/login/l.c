#include "_data_.h"

int
main(int argc, char *argv[])
{
  char     *logname;
  errno_t   err;

  if (argc > 1)
    {
      if (setlogin(argv[1]) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  errno = 0;

  logname = getlogin();
  err = errno;

  if (logname == NULL)
    {
      if (err)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      exit(EXIT_SUCCESS);
    }

  printf("LOGNAME=%s\n", logname);

  exit(EXIT_SUCCESS);
}
