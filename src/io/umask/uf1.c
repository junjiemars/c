#include "_io_.h"
#include <sys/wait.h>


/*
 * A child process created via `fork(2)' inherits its parent's
 * umask. The umask is left unchanged by `execlp(2)'.
 *
 */


static mode_t get_umask(void);


int
main(int argc, char **argv)
{
  mode_t  m;
  pid_t   pid;

  m = get_umask();
  printf("%03o\n", m);


  if (argc > 1)
    {
      exit(EXIT_SUCCESS);
    }

  /* change and fork */
  m = umask(022);

  pid = fork();
  if (pid == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      int rc = execlp(argv[0], argv[0], "X", NULL);
      if (rc == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }
  else
    {
      int rc = waitpid(pid, NULL, 0);
      if (rc == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  exit(EXIT_SUCCESS);
}


mode_t
get_umask(void)
{
  mode_t rc = umask(022);
  umask(rc);
  return rc;
}
