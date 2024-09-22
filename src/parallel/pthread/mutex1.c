#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  int id;
  int count;
  pthread_mutex_t lock;
} thread_state_t;

static thread_state_t *state;

static void *race (void *arg);
static thread_state_t *alloc (int);
static void hold (thread_state_t *);
static void drop (thread_state_t *);

int
main (void)
{
  int rc;
  pthread_t *ts;

  state = alloc (0);
  if (state == NULL)
    {
      fprintf (stderr, "!panic, protected_alloc\n");
      return 1;
    }

  if ((ts = malloc (sizeof (pthread_t) * N_THREAD)) == NULL)
    {
      perror (NULL);
      return 1;
    }

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_create (&ts[i], 0, race, &ts[i]);
      if (rc)
        {
          perror ("!panic, pthread_create");
          goto clean_exit;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (ts[i], NULL);
      if (rc != 0)
        {
          perror ("!panic, pthread_join");
        }
    }

clean_exit:
  drop (state);
  free (ts);
  return rc;
}

void *
race (void *arg)
{
  thread_state_t *state = (thread_state_t *)arg;

  hold (state);
  sleep (1);
  drop (state);
  return arg;
}
thread_state_t *
alloc (int id)
{
  thread_state_t *p = NULL;

  if ((p = malloc (sizeof (thread_state_t))) != NULL)
    {
      p->id = id;
      p->count = 1;
      if (pthread_mutex_init (&p->lock, NULL) != 0)
        {
          free (p);
          return NULL;
        }
    }
  return p;
}

void
hold (thread_state_t *p)
{
  pthread_t tid = pthread_self ();
  pthread_mutex_lock (&p->lock);
  p->count++;
  fprintf (stderr, "#tid=%p count=%d\n", tid, p->count);
  pthread_mutex_unlock (&p->lock);
}

void
drop (thread_state_t *p)
{
  pthread_mutex_lock (&p->lock);
  if (--p->count == 0)
    {
      pthread_mutex_unlock (&p->lock);
      pthread_mutex_destroy (&p->lock);
      free (p);
    }
  else
    {
      pthread_mutex_unlock (&p->lock);
    }
}
