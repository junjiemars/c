#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4

static int count;
static void init_routine (void);

int
main (void)
{
  int rc;
  pthread_once_t once = PTHREAD_ONCE_INIT;

  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_once (&once, init_routine);
      if (rc)
        {
          perror (NULL);
        }
    }
  assert (count == 1 && "init just only once");

  return 0;
}

void
init_routine (void)
{
  pthread_t tid;
  ++count;

  tid = pthread_self ();
  fprintf (stderr, "#tid = %p, count = %i\n", &tid, count);
}
