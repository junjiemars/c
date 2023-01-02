#include "_process_.h"


extern char  **environ;

static void  print_env(const char *, pid_t);


int
main(void)
{
  pid_t  pid;

  setenv("X1", "x", 1);

  pid = fork();
  if (0 == pid)
    {
      pid_t  pc  =  getpid();
      printf("child id = %i\n", pc);

      setenv("X2", "xx", 1);

      print_env("X1", pc);
      print_env("X2", pc);
      printf("[pid=%i] environ at %p\n", pc, environ);
    }
  else
    {
      pid_t  pp  =  getpid();
      printf("parent id = %i\n", pp);

      waitpid(pid, NULL, 0);

      print_env("X1", pp);
      print_env("X2", pp);
      printf("[pid=%i] environ at %8p\n", pp, environ);
    }

  exit(EXIT_SUCCESS);
}

void
print_env(const char *name, pid_t pid)
{
  printf("[pid=%i] %s = %s\n", pid, name, getenv(name));
}
