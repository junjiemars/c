#include "_signal_.h"

static void on_sig_chld (int, siginfo_t *, void *);

static int seconds = 1;
static int sa_flags = 0;

int
main (int argc, char **argv)
{
  pid_t pid;
  struct sigaction act;

  printf ("%d\n", getpid ());

  if (argc > 1)
    {
      seconds = atoi (argv[1]);
    }
  if (argc > 2)
    {
      sscanf (argv[2], "%x", &sa_flags);
    }

  act.sa_sigaction = on_sig_chld;
  act.sa_flags = SA_SIGINFO | sa_flags;
  sigemptyset (&act.sa_mask);
  if (sigaction (SIGCHLD, &act, NULL) == -1)
    {
      perror (NULL);
      _exit (1);
    }

  if ((pid = fork ()) == -1)
    {
      perror (NULL);
      _exit (1);
    }
  else if (0 == pid) /* in child process */
    {
      sleep (seconds);
      _exit (0x11223344);
    }

  pause ();

  _exit (0);
}

void
on_sig_chld (int signo, siginfo_t *info, void *ctx)
{
  if (SIGCHLD == signo)
    {
      assert (info->si_code == CLD_EXITED && "should child has exited");

      printf ("# %s signo=%d "
              "pid=%d uid=%d status=0x%0x errno=%d code=%d ctx=%p\n",
              _str_ (SIGCHLD), info->si_signo, info->si_pid, info->si_uid,
              info->si_status, info->si_errno, info->si_code, ctx);
    }
}
