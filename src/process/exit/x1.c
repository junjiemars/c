#include "_process_.h"

int
main (int argc, char *argv[])
{
  pid_t pid;
  int status;
  int signal = 0;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <status> [signal]\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  sscanf (argv[1], "%x", &status);
  if (argc > 2)
    {
      signal = atoi (argv[2]);
    }

  printf ("parent pid: %d\n", getpid ());

  if ((pid = fork ()) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      fprintf (stderr, "child pid: %d\n", getpid ());
      /* note: no newline */
      printf ("child output ...");
      if (signal > 0)
        {
          pause ();
        }
      _exit (status);
    }

  if (signal > 0)
    {
      kill (pid, signal);
    }

  if (waitpid (pid, &status, 0) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("waitpid get state: 0x%0x\n", status);

  if (WIFEXITED (status))
    {
      printf ("child normal exit(0x%0x)\n", WEXITSTATUS (status));
    }
  else if (WIFSIGNALED (status))
    {
      printf ("child signed by %d, core dump: %d\n", WTERMSIG (status),
              WCOREDUMP (status));
    }
  else if (WIFSTOPPED (status))
    {
      printf ("child stopped by %d\n", WSTOPSIG (status));
    }
  else if (WIFCONTINUED (status))
    {
      printf ("child continued by %d\n", WSTOPSIG (status));
    }

  exit (EXIT_SUCCESS);
}
