#include "_parallel_.h"
#include <pthread.h>

/*
 * 1. answer the 3.Q in `priviate.c'.
 *
 */

#define N_THREAD 4

typedef struct thread_state_s
{
  int sn;
} thread_state_t;

static pthread_once_t once = PTHREAD_ONCE_INIT;
/* static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; */
static pthread_key_t key;

static void *race (void *);
static void init (void);
static void drop (void *);

int
main (void)
{
  int rc;
  int retval;
  pthread_t tids[N_THREAD];

  /* create threads */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_create (&tids[i], NULL, race, (void *)&i);
      if (rc)
        {
          perror (NULL);
        }
    }

  /* join threads */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (tids[i], (void **)&retval);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_join));
        }
    }

  return rc;
}

void
init (void)
{
  int rc;
  pthread_t tid = pthread_self ();

  rc = pthread_key_create (&key, drop);
  if (rc)
    {
      perror ("!panic, " _str_ (pthread_key_create));
      exit (rc);
    }
  fprintf (stderr, "# init tid=0x%0zx\n", (size_t)tid);
}

void *
race (void *arg)
{
  int rc;
  int sn = *(int *)arg;
  pthread_t tid = pthread_self ();
  thread_state_t *state;

  pthread_once (&once, init);

  /* pthread_mutex_lock (&lock); */

  state = pthread_getspecific (key);
  if (state == NULL)
    {
      if ((state = malloc (sizeof (thread_state_t))) == NULL)
        {
          rc = errno;
          perror ("!panic, " _str_ (malloc));
          exit (rc);
        }
    }
  state->sn = sn;
  rc = pthread_setspecific (key, state);
  if (rc)
    {
      perror ("!panic, " _str_ (pthread_setspecific));
      exit (rc);
    }
  fprintf (stderr, "# race tid=0x%0zx sn=%02i state=%02i\n", (size_t)tid, sn,
           state->sn);

  /* pthread_mutex_unlock (&lock); */

  sleep (1);
  return arg;
}

void
drop (void *arg)
{
  pthread_t tid = pthread_self ();
  thread_state_t *state = (thread_state_t *)arg;

  if (state)
    {
      fprintf (stderr, "# drop tid=0x%0zx state=%02i\n", (size_t)tid,
               state->sn);
      free (state);
    }
}
