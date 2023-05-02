#include "_process_.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * 1. stdout is line buffered in terminal.
 * 2. stdout is fully buffered in file.
 * 3. vfork(2) had been deprecated on macOS.
 *
 */

static int g_var = 1;

int
main (void)
{
  pid_t pid;
  int a_var = 2;

  printf ("# before fork\n");

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      exit (1);
    }
  else if (pid == 0)
    {
      ++g_var;
      ++a_var;

      printf ("child: pid=%d\n", getpid ());
      /* exit(3) -> fclose (stdout); */
      _exit (EXIT_SUCCESS);
    }
  else
    {
      waitpid (pid, NULL, 0);
      printf ("parent: pid=%d, g_var=%d, a_var=%d\n", getpid (), g_var, a_var);
    }

  exit (EXIT_SUCCESS);
}
