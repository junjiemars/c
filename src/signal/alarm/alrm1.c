#include <signal.h>
#include <stdio.h>
#include <sys/time.h>

/*
 * emulates POSIX `alarm(2)'.
 *
 * https://pubs.opengroup.org/onlinepubs/9699919799/functions/alarm.html#tag_16_19
 *
 */

unsigned int
alarm (unsigned int nsecs)
{
  struct itimerval o;
  struct itimerval n = { .it_interval = { 0 }, .it_value = { nsecs, 0 } };

  setitimer (ITIMER_REAL, &n, &o);

  return o.it_value.tv_sec + o.it_value.tv_usec / 1000000;
}
