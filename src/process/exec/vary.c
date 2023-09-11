#include "_process_.h"

/*
 * Exhibit how `exec' sequence functions been called.
 *
 * `l': passing argument as List.
 * `p': using PATH environment variable.
 * `e': passing Environment vector.
 * `v': passing argument as Vector.
 *
 */

int
main (int argc, char *argv[])
{
  int rc = 0;
  char *const vargv[] = { _FILE_NAME_, "a", "b", "c", 0 };
  extern char **environ;

  if (argc < 2)
    {
      printf ("usage: argv[1] == exec...\n");
      return 0;
    }
  printf ("%s------------\n", argv[1]);

  if (0 == strcmp ("execl", argv[1]))
    {
      rc = execl (_PATH_NAME_, _FILE_NAME_, "a", "b", "c", (char *)0);
    }
  else if (0 == strcmp ("execlp", argv[1]))
    {
      rc = execlp (_FILE_NAME_, _FILE_NAME_, "a", "b", "c", (char *)0);
    }
  else if (0 == strcmp ("execle", argv[1]))
    {
      rc = execle (_PATH_NAME_, _FILE_NAME_, "a", "b", "c", (char *)0,
                   environ);
    }
  else if (0 == strcmp ("execv", argv[1]))
    {
      rc = execv (_PATH_NAME_, vargv);
    }
  else if (0 == strcmp ("execvp", argv[1]))
    {
      rc = execvp (_FILE_NAME_, vargv);
    }
  else if (0 == strcmp ("execve", argv[1]))
    {
      rc = execve (_PATH_NAME_, vargv, environ);
    }
  else
    {
      printf ("!panic: unknown exec fn\n");
    }

  if (rc == -1)
    {
      perror ("!panic:");
    }

  exit (EXIT_SUCCESS);
}
