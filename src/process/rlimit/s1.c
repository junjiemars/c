#include "_process_.h"

static void pr_stack (const void *);
static void on_sig_alrm (int);

int
main (void)
{
  struct rlimit rl;
  stack_t ss;
  struct sigaction sa;

  if (getrlimit (RLIMIT_STACK, &rl) == -1)
    {
      perror (NULL);
      return 1;
    }
  printf ("%s: cur = %li\n", _str_ (RLIMIT_STACK), (long)rl.rlim_cur);
  pr_stack (&rl);

  if ((ss.ss_sp = malloc (MINSIGSTKSZ)) == NULL)
    {
      perror (NULL);
      return 1;
    }
  ss.ss_size = MINSIGSTKSZ;
#if (DARWIN)
  ss.ss_flags = 0;
#else
  ss.ss_flags = SS_ONSTACK;
#endif
  if (sigaltstack (&ss, (stack_t *)0) == -1)
    {
      perror (NULL);
      return 1;
    }
  pr_stack (&rl);

  sa.sa_handler = on_sig_alrm;
  sa.sa_flags = SA_ONSTACK;
  if (sigaction (SIGALRM, &sa, NULL) == -1)
    {
      perror (NULL);
      return 1;
    }
  kill (getpid (), SIGALRM);

  pr_stack (&rl);

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
  printf ("%14p %4li %8li %14p %14p\n", oss.ss_sp, (long)oss.ss_flags,
          (long)oss.ss_size, addr, oss.ss_sp + MINSIGSTKSZ);
  assert (oss.ss_flags != SS_ONSTACK
          || (addr > oss.ss_sp
              && addr < (oss.ss_sp + MINSIGSTKSZ)));
}
