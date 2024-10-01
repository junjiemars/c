#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 2

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static void *race (void *);

int
main (void)
{
  int rc;
  pthread_t tids[N_THREAD];

  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_create (&tids[i], NULL, race, (void *)&i);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_create));
          return rc;
        }
    }

  for (int quit = N_THREAD; quit > 0; quit--)
    {
      rc = pthread_cond_wait (&cond, &mutex);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_cond_wait));
          return rc;
        }
    }

  rc = pthread_mutex_destroy (&mutex);
  if (rc)
    {
      perror ("!panic, " _str_ (pthread_mutex_destroy));
    }

  return rc;
}

void *
race (void *arg)
{
  int rc;
  int id = *(int *)arg;
  pthread_t tid = pthread_self ();

  fprintf (stderr, "#%02i tid=%p signal ...\n", id, &tid);

  rc = pthread_cond_signal (&cond);
  if (rc)
    {
      fprintf (stderr, "#%02i tid=%p signal%s.\n", id, &tid, strerror(rc));
    }

  return arg;
}
