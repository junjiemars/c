#include "_process_.h"

static void pr_stack (const void *);
static void on_sig_alrm (int);

int
main (void)
{
  struct rlimit rl;
  stack_t ss;

  if (getrlimit (RLIMIT_STACK, &rl) == -1)
    {
      perror (NULL);
      return 1;
    }
  printf ("%s: cur = %li\n", _str_ (RLIMIT_STACK), (long)rl.rlim_cur);
  pr_stack (&ss);

  ss.ss_sp = malloc (MINSIGSTKSZ);
  if (ss.ss_sp == NULL)
    {
      perror (NULL);
      return 1;
    }
  ss.ss_size = MINSIGSTKSZ;
  ss.ss_flags = SS_ONSTACK;
  if (sigaltstack (&ss, (stack_t *)0) == -1)
    {
      perror (NULL);
      return 1;
    }
  pr_stack (&ss);

  if (signal (SIGALRM, on_sig_alrm) == SIG_ERR)
    {
      perror (NULL);
      return 1;
    }
  kill (0, SIGALRM);

  return 0;
}

void
on_sig_alrm (int sig)
{
  int auto1 = 0;
  if (sig == SIGALRM)
    {
      auto1 += SIGALRM;
      pr_stack ((char *)&auto1);
    }
}

void
pr_stack (const void *addr)
{
  stack_t oss;
  if (sigaltstack (NULL, &oss) == -1)
    {
      perror (NULL);
      return;
    }
  printf ("%14p %4li %8li %14p\n", oss.ss_sp, (long)oss.ss_flags,
          (long)oss.ss_size, addr);
}
