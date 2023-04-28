#include "_process_.h"

int
main(int argc, char *argv[])
{
  id_t  nice  =  -20, old;

  if (argc < 2)
    {
      fprintf(stdout, "usage: [nice]\n");
    }
  else
    {
      nice = (id_t) atoi(argv[1]);
    }

  errno = 0;
  old = getpriority(PRIO_PROCESS, 0);
  if (errno)
    {
      perror(NULL);
      exit(1);
    }

  if (setpriority(PRIO_PROCESS, 0, nice) == -1)
    {
      perror(NULL);
      exit(1);
    }

  printf("nice from %d to %d\n", old, nice);

  exit(0);
}
