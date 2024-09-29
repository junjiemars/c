#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 2
#define N_MUTEX N_THREAD
#define N_ERRSTR 128

typedef struct thread_state_s
{
  long sn;
  pthread_t tid;
} thread_state_t;

static int opt_has_deadlock = 0;
static int race_counter = 0;
static pthread_mutex_t mutex[N_MUTEX];
static thread_state_t state[N_THREAD];

static void *race (void *arg);

int
main (int argc, char **argv)
{
  int rc = 0;

  if (argc > 1)
    {
      opt_has_deadlock = atoi (argv[1]);
    }

  /* init mutex */
  for (long i = 0; i < N_MUTEX; i++)
    {
      rc = pthread_mutex_init (&mutex[i], NULL);
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
      rc = pthread_create (&state[i].tid, NULL, race, &state[i]);
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
  for (long i = 0; i < N_MUTEX; i++)
    {
      rc = pthread_mutex_destroy (&mutex[i]);
      if (rc)
        {
          perror ("!panic, pthread_mutex_destroy");
        }
    }

  return 0;
}

void *
race (void *arg)
{
  int rc;
  int n_out = 0;
  int lock1 = 0, lock2 = 0;
  thread_state_t *state = (thread_state_t *)arg;
  pthread_mutex_t *mx1, *mx2;
  char errstr[N_ERRSTR];

  fprintf (stderr, ">%d #%02li tid=%p counter=%02i lock=%d:%d\n", ++n_out,
           state->sn, &state->tid, race_counter, lock1, lock2);

  mx1 = &mutex[(state->sn + 0) % N_MUTEX];
  mx2 = &mutex[(state->sn + 1) % N_MUTEX];

  rc = pthread_mutex_trylock (mx1);
  if (rc)
    {
      snprintf (errstr, N_ERRSTR, ">%d !panic, #%02li mutex=%p lock=%d:%d %s",
                ++n_out, state->sn, mx1, lock1, lock2,
                _str_ (pthread_mutex_trylock));
      perror (errstr);
    }
  else
    {
      fprintf (stderr, ">%d #%02li tid=%p counter=%02i mutex=%p lock=%d:%d\n",
               ++n_out, state->sn, &state->tid, race_counter, mx1, ++lock1,
               lock2);
    }
  sleep (1);

  if (opt_has_deadlock)
    {
      rc = pthread_mutex_trylock (mx2);
      if (rc)
        {
          /* EBUSY on Darwin */
          snprintf (errstr, N_ERRSTR,
                    ">%d !panic, #%02li mutex=%p lock=%d:%d %s", ++n_out,
                    state->sn, mx2, lock1, lock2,
                    _str_ (pthread_mutex_trylock));
          perror (errstr);
        }
      else
        {
          fprintf (stderr,
                   ">%d #%02li tid=%p counter=%02i mutex=%p lock=%d:%d\n",
                   ++n_out, state->sn, &state->tid, race_counter, mx2, lock1,
                   ++lock2);
        }
    }
  ++race_counter;
  fprintf (stderr, ">%d #%02li tid=%p counter=%02i lock=%d:%d\n", ++n_out,
           state->sn, &state->tid, race_counter, lock1, lock2);

  if (opt_has_deadlock)
    {
      if (lock2)
        {
          rc = pthread_mutex_unlock (mx2);
          if (rc)
            {
              snprintf (errstr, N_ERRSTR, ">%d !panic, #%02li lock=%d:%d %s",
                        ++n_out, state->sn, lock1, lock2,
                        _str_ (pthread_mutex_unlock));
              perror (errstr);
            }
          else
            {
              fprintf (stderr,
                       ">%d #%02li tid=%p counter=%02i mutex=%p lock=%d:%d\n",
                       ++n_out, state->sn, &state->tid, race_counter, mx2,
                       lock1, --lock2);
            }
        }
    }

  if (lock1)
    {
      rc = pthread_mutex_unlock (mx1);
      if (rc)
        {
          snprintf (errstr, N_ERRSTR, ">%d !panic, #%02li lock=%d:%d %s",
                    ++n_out, state->sn, lock1, lock2,
                    _str_ (pthread_mutex_unlock));
          perror (errstr);
        }
      else
        {
          fprintf (stderr,
                   ">%d #%02li tid=%p counter=%02i mutex=%p lock=%d:%d\n",
                   ++n_out, state->sn, &state->tid, race_counter, mx1, --lock1,
                   lock2);
        }
    }
  fprintf (stderr, ">%d #%02li tid=%p counter=%02i lock=%d:%d\n", ++n_out,
           state->sn, &state->tid, race_counter, lock1, lock2);
  return arg;
}
