#include "_process_.h"

static int prlimit1 (pid_t, int, const struct rlimit *, struct rlimit *);
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

  if (prlimit1 (pid, RLIMIT_STACK, NULL, &orl) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  pr_rlimit (&orl);

  exit (EXIT_SUCCESS);
}

int
prlimit1 (pid_t pid, int resource, const struct rlimit *new_limit,
          struct rlimit *old_limit)
{
  int rc;

  if (pid != 0)
    {
      pid = 0;
    }

  if (new_limit == NULL)
    {
      rc = getrlimit (resource, old_limit);
    }
  else
    {
      rc = setrlimit (resource, new_limit);
    }
  return rc;
}

void
pr_rlimit (struct rlimit *rl)
{
  printf ("{rlim_cur=%ld, rlim_max=%ld}\n", (long)rl->rlim_cur,
          (long)rl->rlim_max);
}
