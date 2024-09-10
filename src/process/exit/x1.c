#include "_process_.h"

int
main (int argc, char *argv[])
{
  pid_t pid;
  int stated;
  int signaled = 0;
  int sleeped = 0;

  if (argc < 2)
    {
      fprintf (stderr, "usage: %s <stated> [signaled] [sleeped]\n", argv[0]);
      exit (EXIT_FAILURE);
    }
  sscanf (argv[1], "%x", &stated);
  if (argc > 2)
    {
      signaled = atoi (argv[2]);
    }
  if (argc > 3)
    {
      sscanf (argv[3], "%d", &sleeped);
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
      if (signaled > 0)
        {
          pause ();
        }
      _exit (stated);
    }

  if (signaled > 0)
    {
      if (sleeped > 0)
        {
          sleep (sleeped);
        }
      kill (pid, signaled);
    }

  if (waitpid (pid, &stated, 0) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  printf ("waitpid get stated: 0x%x\n", stated);

  if (WIFEXITED (stated))
    {
      printf ("child normal exit(0x%x)\n", WEXITSTATUS (stated));
    }
  else if (WIFSIGNALED (stated))
    {
      printf ("child signed by %d, core dump: %d\n", WTERMSIG (stated),
              WCOREDUMP (stated));
    }
  else if (WIFSTOPPED (stated))
    {
      printf ("child stopped by %d\n", WSTOPSIG (stated));
    }
  else if (WIFCONTINUED (stated))
    {
      printf ("child continued by %d\n", WSTOPSIG (stated));
    }

  exit (EXIT_SUCCESS);
}
