#include <errno.h>
#include <setjmp.h>
#include <time.h>

/*
 * 3rd: emulates POSIX `sleep(3)' using `nanosleep(2)'.
 *
 */

unsigned int sleep (unsigned int);

unsigned int
sleep (unsigned int secs)
{
  struct timespec unslept = { 0 };
  struct timespec req = { .tv_sec = secs, 0 };
  unsigned int sec;

  if (nanosleep (&req, &unslept) == -1)
    {
      if (errno == EINTR)
        {
          sec = (1E+9 - unslept.tv_nsec < 1E+8) ? 1 : 0;
          return (unsigned int)(unslept.tv_sec + sec);
        }
    }

  return 0;
}
