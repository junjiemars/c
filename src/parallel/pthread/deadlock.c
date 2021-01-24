#include <_parallel_.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREAD 2
#define N_MUTEX  2
#define N_ERRSTR 64

typedef struct thread_state_s
{
  long             sn;
  pthread_t        tid;
} thread_state_t;

static int             race_counter = 0;
static pthread_mutex_t mutex[N_MUTEX];

void *race(void *arg);

void *
race(void *arg)
{
  int              rc;
  thread_state_t  *state = (thread_state_t *) arg;
  pthread_mutex_t *m1, *m2;
  char             errstr[N_ERRSTR];

  fprintf(stderr, "> #%02li, tid=0x%016zx, counter=%02i\n",
          state->sn,
          (long) state->tid,
          race_counter);

  m1 = &mutex[(state->sn+0) % N_MUTEX];
  m2 = &mutex[(state->sn+1) % N_MUTEX];

  rc = pthread_mutex_trylock(m1);
  if (rc)
    {
      snprintf(errstr, N_ERRSTR,
               "> !panic, #%02li, pthread_mutex_trylock",
               state->sn);
      perror(errstr);
    }

  sleep(1);

  rc = pthread_mutex_trylock(m2);
  if (rc)
    {
      /* EBUSY on Darwin */
      snprintf(errstr, N_ERRSTR,
               ">> !panic, #%02li, pthread_mutex_trylock",
              state->sn);
      perror(errstr);
    }

  ++race_counter;
  sleep(1);
  fprintf(stderr, ">>> #%02li, tid=0x%016zx, counter=%02i\n",
          state->sn,
          (long) state->tid,
          race_counter);

  rc = pthread_mutex_unlock(m2);
  if (rc)
    {
      snprintf(errstr, N_ERRSTR,
               "<< !panic, #%02li, pthread_mutex_unlock",
               state->sn);
      perror(errstr);
    }

  sleep(1);

  rc = pthread_mutex_unlock(m1);
  if (rc)
    {
      snprintf(errstr, N_ERRSTR,
               "<< !panic, #%02li, pthread_mutex_unlock",
               state->sn);
      perror(errstr);
    }

  fprintf(stderr, "< #%02li, tid=0x%016zx, counter=%02i\n",
          state->sn,
          (long) state->tid,
          race_counter);

  return arg;
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  thread_state_t state[N_THREAD];
  int            rc      = 0;

  /* init mutex */
  for (int i = 0; i < N_MUTEX; i++)
    {
      rc = pthread_mutex_init(&mutex[i], 0);
      if (rc)
        {
          perror("!panic, pthread_mutex_init");
          return 1;
        }
    }

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      state[i].sn = i+1;
      rc = pthread_create(&state[i].tid, 0, race, &state[i]);
      if (rc)
        {
          perror("!panic, pthread_create");
          return 1;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join(state[i].tid, 0);
      if (rc)
        {
          perror("!panic, pthread_join");
        }
    }

  /* destroy mutex */
  for (int i = 0; i < N_MUTEX; i++)
    {
      rc = pthread_mutex_destroy(&mutex[i]);
      if (rc)
        {
          perror("!panic, pthread_mutex_destroy");
        }
    }

  return 0;
}
