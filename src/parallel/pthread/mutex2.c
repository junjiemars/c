#include "_parallel_.h"
#include <pthread.h>

#define N_HASH 3
#define N_THREAD 4
#define _hash_(id) ((unsigned int)id % N_HASH)

static struct thread_state_s *h_states[N_HASH] = { 0 };
static pthread_mutex_t h_lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct thread_state_s
{
  int id;
  int count;
  int workload;
  pthread_mutex_t lock;
  struct thread_state_s *next;
} thread_state_t;

static void *race (void *arg);
static thread_state_t *alloc (int);
static void hold (thread_state_t *);
static thread_state_t *find (int);
static void drop (thread_state_t *);

int
main (void)
{
  int rc;
  void *retval;
  pthread_t threads[N_THREAD];

  /* create threads */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_create (&threads[i], NULL, race, &i);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_create));
          return 1;
        }
    }

  /* join threads */
  for (int i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (threads[i], &retval);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_join));
        }
    }

  return rc;
}

void *
race (void *arg)
{
  int id;
  thread_state_t *s;
  pthread_t tid = pthread_self ();

  id = *(int *)arg;
  s = find (id);
  if (!s)
    {
      if ((s = alloc (id)) == NULL)
        {
          fprintf (stderr, "#tid=0x%0zx, " _str_ (alloc) " failed\n",
                   (size_t)tid);
          return NULL;
        }
    }
  hold (s);
  fprintf (stderr, "#tid=0x%0zx, id=%d, count=%02d, workload=%d\n",
           (size_t)tid, s->id, s->count, s->workload);
  sleep (1);
  drop (s);
  return s;
}

thread_state_t *
alloc (int id)
{
  int idx;
  thread_state_t *s;

  if ((s = malloc (sizeof (thread_state_t))) != NULL)
    {
      s->count = 1;
      if (pthread_mutex_init (&s->lock, NULL) != 0)
        {
          perror ("!panic, " _str_ (pthread_mutex_init));
          free (s);
          return NULL;
        }
      s->id = id;
      idx = _hash_ (id);
      pthread_mutex_lock (&h_lock);
      s->next = h_states[idx];
      h_states[idx] = s;
      pthread_mutex_lock (&s->lock);
      pthread_mutex_unlock (&h_lock);
      pthread_mutex_unlock (&s->lock);
    }
  return s;
}

void
hold (thread_state_t *s)
{
  pthread_mutex_lock (&s->lock);
  s->workload++;
  pthread_mutex_unlock (&s->lock);
}

thread_state_t *
find (int id)
{
  thread_state_t *s;

  pthread_mutex_lock (&h_lock);
  for (s = h_states[_hash_ (id)]; s != NULL; s = s->next)
    {
      if (s->id == id)
        {
          s->count++;
          break;
        }
    }
  pthread_mutex_unlock (&h_lock);
  return s;
}

void
drop (thread_state_t *s)
{
  int idx;
  thread_state_t *p;

  pthread_mutex_lock (&h_lock);
  if (--s->count == 0)
    {
      idx = _hash_ (s->id);
      p = h_states[idx];
      if (p == s)
        {
          h_states[idx] = s->next;
        }
      else
        {
          for (p = p->next; p != s; p = p->next)
            {
              // void
            }
          p->next = s->next;
        }
      pthread_mutex_unlock (&h_lock);
      pthread_mutex_destroy (&s->lock);
      free (s);
    }
  else
    {
      pthread_mutex_unlock (&h_lock);
    }
}
