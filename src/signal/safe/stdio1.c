#include "_signal_.h"

/*
 * 1. the outputs of `printf(3)' are interleaved.
 *
 * 2. stdio is not async-signal-safe.
 *
 * 3. `man signal-safety(7)' on Linux.
 *
 */


static void  on_sig(int);

static volatile int  count  =  8;

static char  alphabet[]  =  "abcdefghijklmnopqrstuvwxyz";
static char  digital[]   =  "0123456789";


int
main(void)
{
  signal(SIGALRM, on_sig);

  alarm(1);

  for (;;)
    {
      printf("%c", alphabet[count % _nof_(alphabet)]);
      pause();
    }
  printf("\n");

  exit(EXIT_SUCCESS);
}


void
on_sig(int signo)
{
  (void) signo;

  if (--count < 1)
    {
      printf("\n");
      exit(EXIT_SUCCESS);
    }

  printf("%c\n", digital[count % _nof_(digital)]);

  alarm(1);
}
