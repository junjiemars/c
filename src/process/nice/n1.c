#include "_process_.h"

/*
 * XSI:
 *
 */

int
main(int argc, char *argv[])
{
  int   n1;
  id_t  n2, o2;
  pid_t pid;

  if (argc < 2)
    {
      n2 = -NZERO;
    }
  else
    {
      n2 = (id_t) atoi(argv[1]);
    }

  errno = 0;
  n1 = nice(0);
  if (errno)
    {
      perror(NULL);
    }
  assert(n1 == 0);
  printf("nice(%d) = %d\n", 0, n1);

  errno = 0;
  o2 = getpriority(PRIO_PROCESS, 0);
  if (errno)
    {
      perror(NULL);
      exit(1);
    }

  if (setpriority(PRIO_PROCESS, 0, n2) == -1)
    {
      perror(NULL);
      exit(1);
    }

  if ((pid = fork()) == -1)
    {
      perror(NULL);
      exit(1);
    }
  else if (pid == 0)
    {
      id_t  c;
      errno = 0;
      c = getpriority(PRIO_PROCESS, 0);
      if (errno)
        {
          perror(NULL);
          exit(1);
        }
      printf("child's nice is %d\n", c);
      exit(0);
    }
  else
    {
      errno = 0;
      n2 = getpriority(PRIO_PROCESS, 0);
      if (errno)
        {
          perror(NULL);
          exit(1);
        }
      printf("nice from %d to %d\n", o2, n2);
    }

  exit(0);
}
