#include <_parallel_.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREAD 2

typedef struct thread_state_s
{
  long            offset;
  long            sn[N_THREAD];
  pthread_t       tid[N_THREAD];
  pthread_mutex_t mutex[N_THREAD];
} thread_state_t;

static int race_counter = 0;
void *race(void *arg);

void *
race(void *arg)
{
  int              rc;
  thread_state_t  *state = (thread_state_t *) arg;
  pthread_mutex_t *mutex1, *mutex2;

  mutex1 = &state->mutex[state->offset+0 % N_THREAD];
  mutex2 = &state->mutex[state->offset+1 % N_THREAD];

  rc = pthread_mutex_lock(mutex1);
  if (rc)
    {
      perror("!panic, pthread_mutex_lock 1");
    }

  sleep(1);

  rc = pthread_mutex_lock(mutex2);
  if (rc)
    {
      perror("!panic, pthread_mutex_lock 2");
    }

  ++race_counter;
  sleep(1);
  fprintf(stderr, "> #%02li, tid=0x%016zx, counter=%02i\n",
          state->sn[state->offset],
          (long) state->tid[state->offset],
          race_counter);

  rc = pthread_mutex_unlock(mutex2);
  if (rc)
    {
      perror("!panic, pthread_mutex_unlock 2");
    }

  sleep(1);

  rc = pthread_mutex_unlock(mutex1);
  if (rc)
    {
      perror("!panic, pthread_mutex_unlock 1");
    }

  return arg;
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  thread_state_t  state;
  int             rc = 0;

  for (long i = 0; i < N_THREAD; i++)
    {
      state.offset = i;

      /* init mutex */
      rc = pthread_mutex_init(&state.mutex[i], 0);
      if (rc)
        {
          perror("!panic, pthread_mutex_init");
          return 1;
        }

      /* create threads */
      state.sn[i] = i+1;
      rc = pthread_create(&state.tid[i], 0, race, &state);
      if (rc)
        {
          perror("!panic, pthread_create");
          return 1;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join(state.tid[i], 0);
      if (rc)
        {
          perror("!panic, pthread_join");
        }
    }

  /* destroy mutex */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_mutex_destroy(&state.mutex[i]);
      if (rc)
        {
          perror("!panic, pthread_mutex_destroy");
        }
    }

  return 0;
}
