#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4
#define N_ERRSTR 64

typedef struct thread_state_s
{
  long sn;
  pthread_t tid;
  pthread_attr_t attr;
} thread_state_t;

static int is_detached (int state, long sn);
static void join_error (int err, long sn);
static void *detached_routine (void *arg);

int
main (void)
{
  int rc;
  int detach;
  pthread_attr_t attr;
  thread_state_t state[N_THREAD];

  /* check main thread detached */
  rc = pthread_attr_init (&attr);
  if (rc)
    {
      perror ("!panic, pthread_attr_init");
      return 1;
    }
  rc = pthread_attr_getdetachstate (&attr, &detach);
  if (rc)
    {
      perror ("!panic, pthread_attr_getdetachstate");
      return 1;
    }
  is_detached (detach, 0);
  rc = pthread_attr_destroy (&attr);
  if (rc)
    {
      perror ("!panic, pthread_attr_destroy");
      return 1;
    }

  /* create joinable and detached threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_attr_init (&state[i].attr);
      if (rc)
        {
          perror ("!panic, pthread_attr_init");
          return 1;
        }

      state[i].sn = i + 1;
      detach = (1 == (state[i].sn & 1)) ? PTHREAD_CREATE_JOINABLE
                                        : PTHREAD_CREATE_DETACHED;

      rc = pthread_attr_setdetachstate (&state[i].attr, detach);
      if (rc)
        {
          perror ("!panic, pthread_attr_setdetachstate");
          return 1;
        }

      rc = pthread_create (&state[i].tid, &state[i].attr, detached_routine,
                           &state[i]);
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
          join_error (rc, state[i].sn);
        }
    }

  return 0;
}

int
is_detached (int state, long sn)
{
  pthread_t tid = pthread_self ();
  switch (state)
    {
    case PTHREAD_CREATE_DETACHED:
      fprintf (stderr, "#%02li, tid=%p, PTHREAD_CREATE_DETACHED\n", sn, &tid);
      return 1;
    case PTHREAD_CREATE_JOINABLE:
      fprintf (stderr, "#%02li, tid=%p, PTHREAD_CREATE_JOINABLE\n", sn, &tid);
      return 0;
    default:
      fprintf (stderr, "#%02li, tid=%p, %i (unknown)\n", sn, &tid, state);
      return 0;
    }
}

void
join_error (int err, long sn)
{
  char ss[N_ERRSTR];
  switch (err)
    {
    case EINVAL:
      snprintf (ss, N_ERRSTR, "!panic, join at #%02li, EINVAL", sn);
      break;
    case ESRCH:
      snprintf (ss, N_ERRSTR, "!panic, join at #%02li, ESRCH", sn);
      break;
    case EDEADLK:
      snprintf (ss, N_ERRSTR, "!panic, join at #%02li, EDEADLK", sn);
      break;
    default:
      snprintf (ss, N_ERRSTR, "!panic, join at #%02li, unknown", sn);
      break;
    }
  perror (ss);
}

void *
detached_routine (void *arg)
{
  int rc;
  int detached;
  thread_state_t *state = (thread_state_t *)arg;

  sleep (1);
  rc = pthread_attr_getdetachstate (&state->attr, &detached);
  if (rc)
    {
      perror ("!panic, detached_routine");
    }
  else
    {
      is_detached (detached, state->sn);
    }
  return state;
}
