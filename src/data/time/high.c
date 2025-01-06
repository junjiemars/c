#include "../_data_.h"
#include <sys/time.h>
#include <time.h>

int
main (void)
{
  time_t utc;
  struct timeval tv;

  if (gettimeofday (&tv, NULL) == -1)
    {
      perror (NULL);
      exit (EXIT_FAILURE);
    }

  time (&utc);
  assert (utc >= tv.tv_sec);

  exit (EXIT_SUCCESS);
}
