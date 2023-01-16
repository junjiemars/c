#include "_signal_.h"
#include <setjmp.h>


static void on_sig_alrm(int signo);

static jmp_buf  env_alrm;
static int      timeout  =  1;


int
main(int argc, char **argv)
{
  int      rc;
  char     buf[sizeof(int)];
  ssize_t  n;

  if (argc > 1)
    {
      timeout = atoi(argv[1]);
    }

  signal(SIGALRM, on_sig_alrm);

  if (setjmp(env_alrm) == timeout)
    {
      printf("! timeout\n");
      exit(EXIT_FAILURE);
    }

  alarm(timeout);
  rc = read(STDIN_FILENO, buf, sizeof(buf));
  if (-1 == rc)
    {
      perror(NULL);
    }
  alarm(0);

  if ((n = write(STDOUT_FILENO, buf, rc)) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}

void
on_sig_alrm(int signo)
{
  if (SIGALRM == signo)
    {
      longjmp(env_alrm, timeout);
    }
}
