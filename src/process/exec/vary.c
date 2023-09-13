#include "_process_.h"
#include <ctype.h>

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
  extern char **environ;

  if (argc < 2)
    {
      printf ("usage: argv[1] == exec\n");
      return 0;
    }
  else if (argc > 5)
    {
      printf ("usage: argc > 5\n");
      return 0;
    }
  printf ("%s------------\n", argv[1]);

  if (0 == strcmp ("execl", argv[1]))
    {
      switch (argc)
        {
        case 5:
          rc = execl (_PATH_NAME_, _FILE_NAME_, argv[2], argv[3], argv[4],
                      (char *)0);
          break;
        case 4:
          rc = execl (_PATH_NAME_, _FILE_NAME_, argv[2], argv[3], (char *)0);
          break;
        case 3:
          rc = execl (_PATH_NAME_, _FILE_NAME_, argv[2], (char *)0);
          break;
        default:
          rc = execl (_PATH_NAME_, _FILE_NAME_, (char *)0);
          break;
        }
    }
  else if (0 == strcmp ("execlp", argv[1]))
    {
      switch (argc)
        {
        case 5:
          rc = execlp (_FILE_NAME_, _FILE_NAME_, argv[2], argv[3], argv[4],
                       (char *)0);
          break;
        case 4:
          rc = execl (_FILE_NAME_, _FILE_NAME_, argv[2], argv[3], (char *)0);
          break;
        case 3:
          rc = execl (_PATH_NAME_, _FILE_NAME_, argv[2], (char *)0);
          break;
        default:
          rc = execlp (_FILE_NAME_, _FILE_NAME_, (char *)0);
          break;
        }
    }
  else if (0 == strcmp ("execle", argv[1]))
    {
      switch (argc)
        {
        case 5:
          rc = execle (_PATH_NAME_, _FILE_NAME_, argv[2], argv[3], argv[4],
                       (char *)0, environ);
          break;
        case 4:
          rc = execle (_PATH_NAME_, _FILE_NAME_, argv[2], argv[3], (char *)0,
                       environ);
          break;
        case 3:
          rc = execle (_PATH_NAME_, _FILE_NAME_, argv[2], (char *)0, environ);
          break;
        default:
          rc = execle (_PATH_NAME_, _FILE_NAME_, (char *)0, environ);
          break;
        }
    }
  else if (0 == strcmp ("execv", argv[1]))
    {
      char **args = 0;
      if (argc > 2)
        {
          args = &argv[2];
        }
      rc = execv (_PATH_NAME_, args);
    }
  else if (0 == strcmp ("execvp", argv[1]))
    {
      char **args = 0;
      if (argc > 2)
        {
          args = &argv[2];
        }
      rc = execvp (_FILE_NAME_, args);
    }
  else if (0 == strcmp ("execve", argv[1]))
    {
      char **args = 0;
      char *xxx = 0;
      if (argc > 2)
        {
          args = &argv[2];
        }
      if ((xxx = getenv ("XXX")) != 0)
        {
          setenv ("YYY", xxx, 0);
        }
      rc = execve (_PATH_NAME_, args, environ);
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
