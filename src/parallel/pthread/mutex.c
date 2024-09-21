#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  long sn;
  pthread_t tid;
} thread_state_t;

static int opt_has_mutex = 0;
static int race_counter = 0;
static pthread_mutex_t mutex;

static void *race (void *arg);

int
main (int argc, char *argv[])
{
  int rc;
  thread_state_t states[N_THREAD];

  if (argc > 1)
    {
      opt_has_mutex = atoi (argv[1]);
    }

  /* init mutex */
  rc = pthread_mutex_init (&mutex, 0);
  if (rc)
    {
      perror ("!panic, pthread_mutex_init");
      return 1;
    }

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      states[i].sn = i + 1;
      rc = pthread_create (&states[i].tid, 0, race, &states[i]);
      if (rc)
        {
          perror ("!panic, pthread_create");
          goto clean_exit;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (states[i].tid, 0);
      if (rc)
        {
          perror ("!panic, pthread_join");
        }
    }

clean_exit:
  if (pthread_mutex_destroy (&mutex) < 0)
    {
      perror ("!panic, pthread_mutex_destroy");
    }

  return rc;
}

void *
race (void *arg)
{
  int rc;
  thread_state_t *state = (thread_state_t *)arg;

  if (opt_has_mutex)
    {
      rc = pthread_mutex_lock (&mutex);
      if (rc)
        {
          perror ("!panic, pthread_mutex_lock");
        }
    }

  ++race_counter;
  sleep (1);

  fprintf (stderr, "> #%02li, tid=0x%016zx, counter=%02i\n", state->sn,
           (long)state->tid, race_counter);

  if (opt_has_mutex)
    {
      rc = pthread_mutex_unlock (&mutex);
      if (rc)
        {
          perror ("!panic, pthread_mutex_unlock");
        }
    }

  return arg;
}
