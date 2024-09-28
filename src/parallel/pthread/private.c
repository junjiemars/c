#include "_parallel_.h"
#include <pthread.h>

/*
 * 1. one thread key allowed assiciate with multiple threads;
 *
 * 2. the associated data will be set null after `free' in `drop'.
 *
 * 3. do we need a lock when call `pthread_setspecific' in `roll'?
 *
 */

#define N_THREAD 2

typedef struct thread_state_s
{
  int sn;
} thread_state_t;

static pthread_key_t key;

static void *race (void *);
static void drop (void *);

int
main (void)
{
  int rc;
  pthread_t threads[N_THREAD];

  /* create thread key */
  rc = pthread_key_create (&key, drop);
  if (rc)
    {
      perror ("!panic, " _str_ (pthread_key_create));
      return 1;
    }

  /* create thread */
  for (int i = 0; i < N_THREAD; i++)
    {
      /* create thread */
      rc = pthread_create (&threads[i], NULL, race, (void *)&i);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_create));
          return rc;
        }
    }

  /* join thread */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (threads[i], 0);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_join));
        }
    }


  /* drop */
  rc = pthread_key_delete (key);
  if (rc)
    {
      perror ("!panic, " _str_ (pthread_key_delete));
    }

  return rc;
}

void *
race (void *arg)
{
  int rc, err;
  int sn = *(int *)arg;
  thread_state_t *state;
  pthread_t tid = pthread_self ();

  state = pthread_getspecific (key);
  if (state == NULL)
    {
      state = malloc (sizeof (thread_state_t));
      if (!state)
        {
          err = errno;
          perror ("!panic, " _str_ (malloc));
          exit (err);
        }
      state->sn = sn;
      rc = pthread_setspecific (key, state);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_setspecific));
          exit (rc);
        }
      fprintf (stderr, "# roll tid=0x%0zx in=%02i set=%02i\n", (size_t)tid, sn,
               sn);
    }
  else
    {
      fprintf (stderr, "# roll tid=0x%0zx in=%02i get=%02i\n", (size_t)tid, sn,
               state->sn);
    }
  sleep (1);
  return arg;
}

void
drop (void *arg)
{
  int sn = *(int *)arg;
  pthread_t tid = pthread_self ();
  thread_state_t *state;

  state = (thread_state_t *)arg;
  if (state == NULL)
    {
      fprintf (stderr, "# drop tid=0x%0zx in=%02i get=null\n", (size_t)tid,
               sn);
    }
  else
    {
      fprintf (stderr, "# drop tid=0x%0zx in=%02i get=%02i\n", (size_t)tid, sn,
               state->sn);
      free (state);
      assert (pthread_getspecific (key) == NULL);
    }
}
