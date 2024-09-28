#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4

static pthread_once_t once = PTHREAD_ONCE_INIT;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void *race (void *);
static void init (void);

int
main (void)
{
  int rc;
  int retval;
  pthread_t tids[N_THREAD];

  /* create threads */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_create (&tids[i], NULL, race, (void *)&i);
      if (rc)
        {
          perror (NULL);
        }
    }

  /* join threads */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (tids[i], (void **)&retval);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_join));
        }
    }

  return rc;
}

void
init (void)
{
  pthread_t tid = pthread_self ();
  fprintf (stderr, "# init tid=0x%0zx\n", (size_t)tid);
}

void *
race (void *arg)
{
  int sn = *(int *)arg;
  pthread_t tid = pthread_self ();

  pthread_once (&once, init);

  pthread_mutex_lock (&lock);
  fprintf (stderr, "# race tid=0x%0zx sn=%02i\n", (size_t)tid, sn);
  pthread_mutex_unlock (&lock);

  sleep (1);
  return arg;
}
