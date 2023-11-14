#include "_process_.h"

/*
 * Simulate `prlimit(1)' command.
 *
 * 1. `prlimit(2)' is a Linux-specific extension.
 *
 */

static void pr_rlimit (struct rlimit *);

int
main (int argc, char **argv)
{
  pid_t pid = 0;
  struct rlimit orl;

  if (argc > 1)
    {
      pid = atoi (argv[1]);
    }

  if (prlimit (pid, RLIMIT_STACK, NULL, &orl) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  pr_rlimit (&orl);

  exit (EXIT_SUCCESS);
}

void
pr_rlimit (struct rlimit *rl)
{
  printf ("{rlim_cur=%ld, rlim_max=%ld}\n", (long)rl->rlim_cur,
          (long)rl->rlim_max);
}
