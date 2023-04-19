#include "_process_.h"

static void  print_pid(void);


int
main(void)
{
  pid_t  pid, pid1;

  print_pid();

  if ((pid = fork()) < 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      print_pid();

      pid1 = fork();

      if (pid1 < 0)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
      else if (pid1 == 0)
        {
          print_pid();
          exit(EXIT_SUCCESS);
        }

      if (waitpid(pid, 0, 0) < 0)
        {
          perror(NULL);
        }
      print_pid();

      exit(EXIT_SUCCESS);
    }

  if (waitpid(pid, 0, 0) < 0)
    {
      perror(NULL);
    }

  print_pid();

  exit(EXIT_SUCCESS);
}

void
print_pid(void)
{
  pid_t  pid, pgid;

  pid = getpid();
  pgid = getpgid(pid);

  printf("pid=%d, pgid=%d\n", pid, pgid);
}
