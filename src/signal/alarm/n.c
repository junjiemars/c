#include "_signal_.h"
#include <stdio.h>
#include <sys/time.h>

/*
 * alarm recursively via `setitimer(2)'.
 *
 */


#define ALRM_N  8
static volatile int  count  =  ALRM_N;


static void on_sig_segv(int sig);
static void on_sig_alrm(int sig);

static void alarm_1s(void);


int
main(void)
{
  volatile int  i  =  0;

  signal(SIGALRM, on_sig_alrm);
  signal(SIGSEGV, on_sig_segv);

  setvbuf(stdout, NULL, _IONBF, 0);

  alarm_1s();

  for (;;)
    {
      i += 1;
    }

  exit(EXIT_SUCCESS);
}


void
on_sig_segv(int sig)
{
  if (SIGSEGV == sig)
    {
      printf("# %s\n", _str_(SIGSEGV));
    }

  exit(EXIT_SUCCESS);
}

void
on_sig_alrm(int sig)
{
  if (SIGALRM == sig)
    {
      printf("# %s\n", _str_(SIGALRM));

      if (--count < 1)
        {
          exit(EXIT_SUCCESS);
        }
    }

  alarm_1s();
}

void
alarm_1s(void)
{
  int               rc;
  struct itimerval  old;
  struct itimerval  itv  =
    {
      .it_interval      =  { 0 },
      .it_value         =  { 1, 0 }
    };

  rc = setitimer(ITIMER_REAL, &itv, &old);
  if (-1 == rc)
    {
      perror(NULL);
    }

}
