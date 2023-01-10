#include "_signal_.h"
#include <setjmp.h>


/*
 * try to fix the race condition between the alarm call and the pause
 * call.
 *
 */


unsigned  sleep(unsigned);

extern void  race(long);

extern unsigned  N;

static jmp_buf  env_alrm;


unsigned
sleep(unsigned nsecs)
{
  if (0 == setjmp(env_alrm))
    {
      alarm(nsecs);

      /* race condition: between alarm and pause */
      race(N);

      pause();
    }

  return alarm(0);
}
