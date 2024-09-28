#include "_parallel_.h"
#include <pthread.h>

#define N_HASH 2
#define N_THREAD 4
#define N_OP 2
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
static thread_state_t *find (int);
static void alloc (void *);
static void drop (void *);

static void (*list_ops[N_OP]) (void *) = { alloc, drop };
static unsigned op_seed = 29;

int
main (void)
{
  int rc;
  int *retval;
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
      rc = pthread_join (threads[i], (void **)&retval);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_join));
          return 1;
        }
    }

  for (int i = 0; i < N_THREAD; i++)
    {
      drop ((void *)&i);
    }

  return rc;
}

void *
race (void *arg)
{
  int id = *(int *)arg;
  void (*op) (void *);

  for (int i = 0; i < N_THREAD; i++)
    {
      op = list_ops[rand_r (&op_seed) % N_OP];
      op ((void *)&id);
    }

  return arg;
}

void
alloc (void *arg)
{
  int rc;
  int id, idx;
  thread_state_t *s;
  pthread_t tid = pthread_self ();

  id = *(int *)arg;

  if ((s = malloc (sizeof (thread_state_t))) != NULL)
    {
      rc = pthread_mutex_init (&s->lock, NULL);
      if (rc)
        {
          perror ("!panic, " _str_ (pthread_mutex_init));
          free (s);
          exit (rc);
        }
      fprintf (stderr, "# alloc tid=0x%0zx id=%02i\n", (size_t)tid, id);

      s->id = id;
      idx = _hash_ (id);

      pthread_mutex_lock (&h_lock);

      s->next = h_states[idx];
      h_states[idx] = s;

      pthread_mutex_lock (&s->lock);
      pthread_mutex_unlock (&h_lock);
      pthread_mutex_unlock (&s->lock);
    }
}

thread_state_t *
find (int id)
{
  thread_state_t *s = NULL;
  pthread_t tid = pthread_self ();

  pthread_mutex_lock (&h_lock);
  for (s = h_states[_hash_ (id)]; s != NULL; s = s->next)
    {
      if (s->id == id)
        {
          fprintf (stderr, "# find tid=0x%0zx id=%02i\n", (size_t)tid, id);
          break;
        }
    }
  pthread_mutex_unlock (&h_lock);
  return s;
}

void
drop (void *arg)
{
  int id;
  int idx;
  thread_state_t *s, *p;
  pthread_t tid = pthread_self ();

  id = *(int *)arg;
  p = find (id);

  if (!p)
    {
      return;
    }

  pthread_mutex_lock (&h_lock);
  idx = _hash_ (p->id);
  s = h_states[idx];
  if (s == p)
    {
      h_states[idx] = s->next;
    }
  else
    {
      for (s = p->next; s != p; s = p->next)
        {
          // void
        }
      s->next = p->next;
    }
  fprintf (stderr, "# drop tid=0x%0zx id=%02i\n", (size_t)tid, id);
  pthread_mutex_unlock (&h_lock);
  pthread_mutex_destroy (&s->lock);
  free (s);
  pthread_mutex_unlock (&h_lock);
}
