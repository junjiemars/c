#include "_signal_.h"
#include <sys/stat.h>
#include <sys/resource.h>


static void  on_sig_xfsz(int);

int
main(void)
{
  ssize_t           r, w;
  char              buf[BUF_SIZE];
  struct stat       ss;
  struct rlimit     fsz;
  struct sigaction  nset;

  fprintf(stderr, "|> %d, BUF_SIZE=%i, RL_FSIZE=%i\n",
          getpid(), BUF_SIZE, RL_FSIZE);

  if (fstat(STDIN_FILENO, &ss) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  fprintf(stderr, "|> in file size %zu bytes\n", (size_t) ss.st_size);

  if (getrlimit(RLIMIT_FSIZE, &fsz) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fsz.rlim_max = fsz.rlim_cur = RL_FSIZE;

  if (setrlimit(RLIMIT_FSIZE, &fsz) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fprintf(stderr, "|> setrlmit %s = { .rlim_cur = %llu, .rlim_max = %llu }\n",
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

  while ((r = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
      errno = 0;
      if ((w = write(STDOUT_FILENO, buf, r)) != r)
        {
          if (errno)
            {
              perror("! write");
            }
          fprintf(stderr, "r(%zd), w(%zd)\n", r, w);
          exit(EXIT_FAILURE);
        }
    }

  if (r < 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}

void
on_sig_xfsz(int signo)
{
  fprintf(stderr, "|> %s(%d) caught\n", _str_(SIGXFSZ), signo);
}
