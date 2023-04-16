#include "_process_.h"

int
main(void)
{
  if (system("date") < 0)
    {
      perror(NULL);
    }

  exit(0);
}
