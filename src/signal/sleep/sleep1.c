#include "_signal_.h"


/*
 * Emulates `sleep(3)'.
 *
 */


unsigned int  sleep(unsigned int);

extern void  race(long);

extern unsigned int  N;


unsigned int
sleep(unsigned int nsecs)
{
  alarm(nsecs);

  /* race condition: between alarm and pause */
  race(N);

  pause();

  return alarm(0);
}
