#include "_signal_.h"
#include <setjmp.h>


/*
 * 3rd: emulates POSIX `sleep(3)' using `nanosleep(2)'.
 *
 */


unsigned int  sleep(unsigned int);


unsigned int
sleep(unsigned int nsecs)
{
  struct timespec  unslept = { 0 };
  struct timespec  req  =  { .tv_sec = nsecs, 0 };

  if (nanosleep(&req, &unslept) == -1)
    {
      if (errno == EINTR)
        {
          return (unsigned int) (unslept.tv_sec + unslept.tv_nsec/1000000000);
        }
    }

  return 0;
}
