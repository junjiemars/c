#include "_signal_.h"
#include <sys/time.h>


/*
 * emulates POSIX `sleep(3)'.
 *
 */


unsigned int  sleep(unsigned int);


unsigned int
sleep(unsigned int nsecs)
{
  alarm(nsecs);

  if (nsecs > 0)
    {
      pause();
    }

  return alarm(0);
}
