#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 1
#define _need_drop_(x) (((x)&1) == 1)

typedef struct thread_state_s
{
  long sn;
} thread_state_t;

static pthread_key_t thread_keys[N_THREAD];

static void *roll (void *);
static void drop (void *);

int
main (void)
{
  int rc;
  pthread_t threads[N_THREAD];
  thread_state_t *states[N_THREAD];

  /* create thread */
  for (long i = 0; i < N_THREAD; i++)
    {
      states[i] = malloc (sizeof (thread_state_t));
      if (!states[i])
        {
          perror ("!panic, " _str_ (malloc));
          return 1;
        }
      states[i]->sn = i;
      void (*drop_fn) (void *) = _need_drop_ (i) ? drop : NULL;

      /* create thread key */
      rc = pthread_key_create (&thread_keys[i], drop_fn);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_key_create));
          return 1;
        }

      /* specify private data */
      rc = pthread_setspecific (thread_keys[i], states[i]);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_setspecific));
          return 1;
        }

      /* create thread */
      rc = pthread_create (&threads[i], 0, roll, (void *)i);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_create) "\n");
          return 1;
        }
    }

  /* join thread */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (threads[i], 0);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_join) "\n");
        }

      /* drop */
      rc = pthread_key_delete (thread_keys[i]);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_key_delete));
        }

      if (!_need_drop_ (i))
        {
          free (states[i]);
        }
    }

  return 0;
}

void *
roll (void *arg)
{
  long sn = (long)arg;
  thread_state_t *state;

  state = pthread_getspecific (thread_keys[sn]);
  if (state == NULL)
    {
      fprintf (stderr, "!panic, %s, no error\n", _str_ (pthread_getspecific));
    }
  else
    {
      pthread_t tid = pthread_self ();
      fprintf (stderr, "#roll tid=0x%0zx in=%02li get=%02li\n", (size_t)tid,
               sn, state->sn);
    }
  sleep (1);
  return arg;
}

void
drop (void *arg)
{
  pthread_t tid = pthread_self ();
  thread_state_t *state = (thread_state_t *)arg;
  fprintf (stderr, "# drop tid=0x%0zx get=%02li\n", (size_t)tid, state->sn);
  if (_need_drop_ (state->sn))
    {
      free (state);
    }
}
