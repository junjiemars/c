#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 2
#define N_MUTEX 2
#define N_ERRSTR 128

typedef struct thread_state_s
{
  long sn;
  pthread_t tid;
} thread_state_t;

static int opt_has_deadlock = 0;
static int race_counter = 0;
static pthread_mutex_t mutex[N_MUTEX];

void *race (void *arg);

void *
race (void *arg)
{
  int rc;
  int n_out = 0;
  thread_state_t *state = (thread_state_t *)arg;
  pthread_mutex_t *mx1, *mx2;
  char errstr[N_ERRSTR];

  fprintf (stderr, ">%d #%02li tid=%p counter=%02i\n", ++n_out, state->sn,
           &state->tid, race_counter);

  mx1 = &mutex[(state->sn + 0) % N_MUTEX];
  mx2 = &mutex[(state->sn + 1) % N_MUTEX];

  rc = pthread_mutex_trylock (mx1);
  if (rc)
    {
      snprintf (errstr, N_ERRSTR, ">%d !panic, #%02li %s", ++n_out, state->sn,
                _str_ (pthread_mutex_trylock));
      perror (errstr);
      goto exit;
    }
  fprintf (stderr, ">%d #%02li tid=%p counter=%02i\n", ++n_out, state->sn,
           &state->tid, race_counter);
  sleep (1);

  if (opt_has_deadlock)
    {
      rc = pthread_mutex_trylock (mx2);
      if (rc)
        {
          /* EBUSY on Darwin */
          snprintf (errstr, N_ERRSTR, ">%d !panic, #%02li %s", ++n_out,
                    state->sn, _str_ (pthread_mutex_trylock));
          perror (errstr);
          goto exit_lock1;
        }
      fprintf (stderr, ">%d #%02li tid=%p counter=%02i\n", ++n_out, state->sn,
               &state->tid, race_counter);
    }

  ++race_counter;
  fprintf (stderr, ">%d #%02li, tid=0x%p counter=%02i\n", ++n_out, state->sn,
           &state->tid, race_counter);

  if (opt_has_deadlock)
    {
      sleep (1);
      rc = pthread_mutex_unlock (mx2);
      if (rc)
        {
          snprintf (errstr, N_ERRSTR, ">%d !panic, #%02li %s", ++n_out,
                    state->sn, _str_ (pthread_mutex_unlock));
          perror (errstr);
        }
      sleep (1);
    }

exit_lock1:
  rc = pthread_mutex_unlock (mx1);
  if (rc)
    {
      snprintf (errstr, N_ERRSTR, ">%d !panic, #%02li %s", ++n_out, state->sn,
                _str_ (pthread_mutex_unlock));
      perror (errstr);
    }
exit:
  fprintf (stderr, ">%d #%02li tid=%p counter=%02i\n", ++n_out, state->sn,
           &state->tid, race_counter);
  return arg;
}

int
main (int argc, char **argv)
{
  int rc = 0;
  thread_state_t state[N_THREAD];

  if (argc > 1)
    {
      opt_has_deadlock = atoi (argv[1]);
    }

  /* init mutex */
  for (int i = 0; i < N_MUTEX; i++)
    {
      rc = pthread_mutex_init (&mutex[i], 0);
      if (rc)
        {
          perror ("!panic, pthread_mutex_init");
          return 1;
        }
    }

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      state[i].sn = i + 1;
      rc = pthread_create (&state[i].tid, 0, race, &state[i]);
      if (rc)
        {
          perror ("!panic, pthread_create");
          return 1;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (state[i].tid, 0);
      if (rc)
        {
          perror ("!panic, pthread_join");
        }
    }

  /* destroy mutex */
  for (int i = 0; i < N_MUTEX; i++)
    {
      rc = pthread_mutex_destroy (&mutex[i]);
      if (rc)
        {
          perror ("!panic, pthread_mutex_destroy");
        }
    }

  return 0;
}
