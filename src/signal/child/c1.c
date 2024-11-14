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
      printf ("1 / %d = %d\n", sa_flags, 1 / sa_flags);
      _exit (0x11223344);
    }

  pause ();

  _exit (0);
}

void
on_sig_chld (int signo, siginfo_t *info, void *ctx)
{
  ucontext_t *c;
  char *code_name;

  if (SIGCHLD == signo)
    {
      switch (info->si_code)
        {
        case CLD_NOOP:
          code_name = _str_ (CLD_NOOP);
          break;
        case CLD_EXITED:
          code_name = _str_ (CLD_EXITED);
          break;
        case CLD_KILLED:
          code_name = _str_ (CLD_KILLED);
          break;
        case CLD_DUMPED:
          code_name = _str_ (CLD_DUMPED);
          break;
        case CLD_TRAPPED:
          code_name = _str_ (CLD_TRAPPED);
          break;
        case CLD_STOPPED:
          code_name = _str_ (CLD_STOPPED);
          break;
        case CLD_CONTINUED:
          code_name = _str_ (CLD_CONTINUED);
          break;
        }

      printf ("# %s(%d) "
              "pid=%d uid=%d status=0x%0x errno=%d code=%s(%d)\n",
              _str_ (SIGCHLD), info->si_signo, info->si_pid, info->si_uid,
              info->si_status, info->si_errno, code_name, info->si_code);

      c = (ucontext_t *)ctx;
      printf ("context:%p\n"
              "  uc_link=%p\n"
              "  uc_sigmask=0x%0x\n"
              "  uc_stack:\n"
              "    ss_sp=%p\n"
              "    ss_size=%zu\n"
              "    ss_flags=%d\n",
              ctx, c->uc_link, c->uc_sigmask, c->uc_stack.ss_sp,
              c->uc_stack.ss_size, c->uc_stack.ss_flags);
    }
}
