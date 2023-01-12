#include "_signal_.h"
#include "_alrm_.h"

#include <stdio.h>
#include <sys/time.h>

/*
 * alarm recursively via `setitimer(2)'.
 *
 */


extern volatile int  alrm_count;


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

      if (--alrm_count < 1)
        {
          exit(EXIT_SUCCESS);
        }
    }

  alarm_1s();
}

void
alarm_1s(void)
{
  struct itimerval  old;
  struct itimerval  itv  =
    {
      .it_interval      =  { 0 },
      .it_value         =  { 1, 0 }
    };

  if (setitimer(ITIMER_REAL, &itv, &old) == -1)
    {
      perror(NULL);
    }

}
