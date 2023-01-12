#include "_signal_.h"

/*
 * 1. the outputs of `printf(3)' are interleaved.
 *
 * 2. stdio is not async-signal-safe.
 *
 * 3. `man signal-safety(7)' on Linux.
 *
 */


static void  on_sig(int, siginfo_t*, void*);

static volatile int  count  =  8;

static char  alpha[]  =  "abcdefghijklmnopqrstuvwxyz";
static char  digit[]   =  "0123456789";


int
main(void)
{
  struct sigaction  act, oact;

  act.sa_sigaction = on_sig;
  act.sa_flags = SA_SIGINFO;

  if (sigaction(SIGALRM, &act, &oact) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  (void) oact;

  alarm(1);

  for (;;)
    {
      printf("%c", alpha[count % _nof_(alpha)]);
      pause();
    }
  printf("\n");

  exit(EXIT_SUCCESS);
}


void
on_sig(int signo, siginfo_t *info, void *ctx)
{
  (void) signo;
  (void) info;
  (void) ctx;

  if (--count < 1)
    {
      printf("\n");
      exit(EXIT_SUCCESS);
    }

  printf("%c\n", digit[count % _nof_(digit)]);

  alarm(1);
}
