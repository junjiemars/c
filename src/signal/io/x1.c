#include "_signal_.h"


static void  on_sig_xfsz(int);


int
main(void)
{
  int               n;
  char              buf[BUF_SIZE];
  struct sigaction  nset;
  struct rlimit     fsz;

  printf("|> %d, %i\n", getpid(), BUF_SIZE);

  if (getrlimit(RLIMIT_FSIZE, &fsz) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fsz.rlim_cur = RL_FSIZE;

  if (setrlimit(RLIMIT_FSIZE, &fsz) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("|> %s = { .rlim_cur = %llu, .rlim_max = %llu }\n",
         _str_(RLIMIT_FSIZE),
         (unsigned long long) fsz.rlim_cur,
         (unsigned long long) fsz.rlim_cur);

  sigemptyset(&nset.sa_mask);
  nset.sa_flags = 0;
  nset.sa_handler = on_sig_xfsz;

  if (sigaction(SIGXFSZ, &nset, NULL) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  while ((n = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
      if (write(STDOUT_FILENO, buf, n) != n)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  if (n < 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}

void
on_sig_xfsz(int signo)
{
  printf("|> %s(%d) caught\n", _str_(SIGXFSZ), signo);
}
