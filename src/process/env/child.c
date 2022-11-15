#include "_process_.h"


extern char **environ;

int
main(void)
{
  int    stat;
  pid_t  pid;

  setenv("X1", "x", 1);

  pid = fork();
  if (0 == pid)
    {
      pid_t pc = getpid();

      setenv("X2", "xx", 1);

      printf("[cid=%i] X1 = %s\n", pc, getenv("X1"));
      printf("[cid=%i] X2 = %s\n", pc, getenv("X2"));
      printf("[cid=%i] environ at %p\n", pc, environ);

    }
  else
    {
      pid_t pp = getpid();

      waitpid(pid, &stat, 0);

      printf("[pid=%i] X1 = %s\n", pp, getenv("X1"));
      printf("[pid=%i] X2 = %s\n", pp, getenv("X2"));
      printf("[pid=%i] environ at %8p\n", pp, environ);
    }

  exit(EXIT_SUCCESS);
}
