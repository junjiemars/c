#include <_parallel_.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  long sn;
  pthread_t tid;
  pthread_mutex_t *mutex;
} thread_state_t;

static int opt_has_mutex = 0;
static int race_counter = 0;
void *race(void *arg);

void *
race(void *arg)
{
  int             rc;
  thread_state_t *state = (thread_state_t *) arg;

  if (opt_has_mutex)
    {
      rc = pthread_mutex_lock(state->mutex);
      if (rc)
        {
          perror("!panic, pthread_mutex_lock");
        }
    }

  ++race_counter;
  sleep(1);

  fprintf(stderr, "> #%02li, tid=0x%016zx, counter=%02i\n",
          state->sn, (long) state->tid, race_counter);

  if (opt_has_mutex)
    {
      rc = pthread_mutex_unlock(state->mutex);
      if (rc)
        {
          perror("!panic, pthread_mutex_unlock");
        }
    }

  return arg;
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  thread_state_t  states[N_THREAD];
  pthread_mutex_t mutex;
  int             rc;

  if (argc > 1)
    {
      opt_has_mutex = atoi(argv[1]);
    }

  /* init mutex */
  rc = pthread_mutex_init(&mutex, 0);
  if (rc)
    {
      perror("!panic, pthread_mutex_init");
      return 1;
    }

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      states[i].sn = i+1;
      states[i].mutex = &mutex;

      rc = pthread_create(&states[i].tid, 0, race, &states[i]);
      if (rc)
        {
          perror("!panic, pthread_create");
          return 1;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join(states[i].tid, 0);
      if (rc)
        {
          perror("!panic, pthread_join");
        }
    }

  rc = pthread_mutex_destroy(&mutex);
  if (rc)
    {
      perror("!panic, pthread_mutex_destroy");
    }

  return 0;
}
