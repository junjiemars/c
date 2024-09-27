#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 2

typedef struct thread_state_s
{
  int sn;
} thread_state_t;

static pthread_key_t key;

static void *roll (void *);
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
      rc = pthread_create (&threads[i], NULL, roll, (void *)&i);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_create));
          return 1;
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

  return 0;
}

void *
roll (void *arg)
{
  int sn = *(int *)arg;
  thread_state_t *state;
  pthread_t tid = pthread_self ();

  state = pthread_getspecific (key);
  if (state == NULL)
    {
      state = malloc (sizeof (thread_state_t));
      if (!state)
        {
          perror ("!panic, " _str_ (malloc));
          exit (1);
        }
      state->sn = sn;
      if (pthread_setspecific (key, state) != 0)
        {
          perror ("!panic, " _str_ (pthread_setspecific));
          exit (1);
        }
      fprintf (stderr, "# roll tid=0x%0zx set in=%02i\n", (size_t)tid, sn);
    }
  else
    {
      fprintf (stderr, "# roll tid=0x%0zx get in=%02i get=%02i\n", (size_t)tid,
               sn, state->sn);
    }
  sleep (1);
  return arg;
}

void
drop (void *arg)
{
  int sn = *(int *)arg;
  pthread_t tid = pthread_self ();
  thread_state_t *state = (thread_state_t *)arg;
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
    }
}
