#include "_process_.h"

/*
 * orphan process group
 *
 */

static void on_sig_hup (int);
static void pr_ids (const char *);

static int N = 0;

int
main (int argc, char *argv[])
{
  pid_t pid;

  if (argc > 1)
    {
      N = atoi (argv[1]);
    }

  fprintf (stderr, "# parent: pid=%d enter ...\n", getpid ());
  pr_ids ("parent");

  if ((pid = fork ()) < 0)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }
  else if (pid == 0)
    {
      char c;

      fprintf (stderr, "# child: pid=%d enter ...\n", getpid ());
      pr_ids ("child");

      if (signal (SIGHUP, on_sig_hup) == SIG_ERR)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }
      kill (getpid (), SIGTSTP);

      pr_ids ("child");

      if (read (STDIN_FILENO, &c, 1) != 1)
        {
          int err = errno;
          fprintf (stderr, "# %d read failed(%d): %s\n", getpid (), err,
                   strerror (err));
        }

      fprintf (stderr, "# child: pid=%d exit ...\n", getpid ());
      exit (EXIT_SUCCESS);
    }

  sleep (N);
  fprintf (stderr, "# parent: pid=%d exit ...\n", getpid ());

  exit (EXIT_SUCCESS);
}

void
on_sig_hup (int signo)
{
  if (signo == SIGHUP)
    {
      fprintf (stderr, "# %d caught(%s(%d))\n", getpid (), _str_ (SIGHUP),
               signo);
    }
}

void
pr_ids (const char *who)
{
  fprintf (stderr, "%s: pid=%d, ppid=%d, pgrp=%d, tpgrp=%d, sid=%d\n", who,
           getpid (), getppid (), getpgrp (), tcgetpgrp (STDIN_FILENO),
           getsid (getpid ()));
}
