#include "_process_.h"

int
main(int argc, char *argv[])
{
  pid_t  pid;
  int    status;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <status>\n", argv[0]);
      exit(EXIT_FAILURE);
    }
  sscanf(argv[1], "%x", &status);

  if ((pid = fork()) < 0)
    {
      perror(NULL);
    }
  else if (pid == 0)
    {
      printf("child output ...");
      _exit(status);
    }

  if (waitpid(pid, &status, 0) < 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (WIFEXITED(status))
    {
      printf("child exit(0x%0x)\n", WEXITSTATUS(status));
    }

  exit(EXIT_SUCCESS);
}
