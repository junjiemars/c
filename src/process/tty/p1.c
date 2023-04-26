#include "_process_.h"

int
main(void)
{
  int    err;
  char  *name;

  err = 0;
  if (isatty(STDIN_FILENO) == 0)
    {
      if (err)
        {
          perror("isatty");
        }
      else
        {
          name = ttyname(STDIN_FILENO);
          if (name == NULL)
            {
              perror("ttyname");
              exit(1);
            }
          printf("stdin is a tty: %s\n", name);
        }
    }
  else
    {
      printf("stdin is not a tty\n");
    }

  exit(0);
}
