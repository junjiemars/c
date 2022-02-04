#include "_signal_.h"
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>


#define READ_TIMEOUT  1

static jmp_buf  read_env;


static void on_sig_alrm(int signo);

static void
on_sig_alrm(int signo)
{
  if (SIGALRM == signo)
    {
      longjmp(read_env, READ_TIMEOUT);
    }
}

int
main(void)
{
  int   rc;
  char  buf[sizeof(int)];

  signal(SIGALRM, on_sig_alrm);

  switch (setjmp(read_env))
    {
    case READ_TIMEOUT:
      printf("!read: timeout\n");
      return READ_TIMEOUT;

    default:
      break;
     }

  alarm(10);
  rc = read(STDIN_FILENO, buf, sizeof(buf));
  if (-1 == rc)
    {
      perror(NULL);
    }
  alarm(0);

  write(STDOUT_FILENO, buf, rc);

  return 0;
}
