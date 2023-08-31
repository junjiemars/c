#include "_process_.h"

/*
 * How the pathname, filename and environment passed to `execve'?
 *
 */

int
main (void)
{
  int rc = 0;
  pid_t pid;
  char *const env[] = { "XXX=xxx", 0 };

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      rc = execle (_PATH_NAME_, _FILE_NAME_, "a", "b", "c", (char *)0, env);
      if (rc == -1)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }
      exit (EXIT_SUCCESS);
    }

  pid = waitpid (pid, NULL, 0);
  if (pid == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  exit (EXIT_SUCCESS);
}
