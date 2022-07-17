#include <_signal_.h>

#define BUF_SIZE  512

static void on_sig_tstp(int);


int
main(void)
{
  int   n;
  char  buf[BUF_SIZE];

  printf("%d\n", getpid());

  if (SIG_DFL == signal(SIGTSTP, on_sig_tstp))
    {
      printf("# %s catching...\n", _str_(SIGTSTP));
      signal(SIGTSTP, on_sig_tstp);
    }

  while ((n = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
      if (write(STDOUT_FILENO, buf, n) != n)
        {
          printf("! write error\n");
        }
    }
  if (n < 0)
    {
      perror(NULL);
    }

  exit(EXIT_SUCCESS);
}

void
on_sig_tstp(int signo)
{
  sigset_t  set;

  if (SIGTSTP != signo)
    {
      printf("# %d skip\n", signo);
      return;
    }
  printf("# %s caught\n", _str_(SIGTSTP));

  sigemptyset(&set);
  sigaddset(&set, SIGTSTP);
  if (-1 == sigprocmask(SIG_UNBLOCK, &set, NULL))
    {
      perror(NULL);
    }
  else
    {
      printf("! %s unblocked\n", _str_(SIGTSTP));
    }

  if (SIG_ERR == signal(SIGTSTP, SIG_DFL))
    {
      perror(NULL);
    }
  else
    {
      printf("! %s restore to default\n", _str_(SIGTSTP));
    }

  printf("! %s rasing...\n", _str_(SIGTSTP));
  kill(getpid(), SIGTSTP);

  if (SIG_ERR == signal(SIGTSTP, on_sig_tstp))
    {
      perror(NULL);
    }
  else
    {
      printf("! %s catching...\n", _str_(SIGTSTP));
    }
}
