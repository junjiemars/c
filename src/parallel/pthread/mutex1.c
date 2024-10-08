#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  int count;
  pthread_mutex_t lock;
} thread_state_t;

static void *race (void *arg);
static thread_state_t *alloc (void);
static void hold (thread_state_t *);
static void drop (thread_state_t *);

int
main (void)
{
  int rc;
  void *retval;
  pthread_t threads[N_THREAD];
  thread_state_t *state;

  state = alloc ();
  if (state == NULL)
    {
      fprintf (stderr, "!panic, " _str_ (alloc) "\n");
      return 1;
    }

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_create (&threads[i], NULL, race, state);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_create));
          return 1;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (threads[i], &retval);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_join));
        }
    }

  drop (state);
  return rc;
}

void *
race (void *arg)
{
  pthread_t tid = pthread_self ();
  thread_state_t *s = (thread_state_t *)arg;
  hold (s);
  fprintf (stderr, "#tid=0x%0zx, count=%02d\n", (size_t)tid, s->count);
  sleep (1);
  drop (s);
  return arg;
}

thread_state_t *
alloc (void)
{
  thread_state_t *s = NULL;

  if ((s = malloc (sizeof (thread_state_t))) != NULL)
    {
      s->count = 1;
      if (pthread_mutex_init (&s->lock, NULL) != 0)
        {
          perror ("!panic, " _str_ (pthread_mutex_init));
          free (s);
          return NULL;
        }
    }
  return s;
}

void
hold (thread_state_t *s)
{
  pthread_mutex_lock (&s->lock);
  s->count++;
  pthread_mutex_unlock (&s->lock);
}

void
drop (thread_state_t *s)
{
  pthread_mutex_lock (&s->lock);
  if (--s->count == 0)
    {
      pthread_mutex_unlock (&s->lock);
      pthread_mutex_destroy (&s->lock);
      free (s);
    }
  else
    {
      pthread_mutex_unlock (&s->lock);
    }
}
