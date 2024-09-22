#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  unsigned int idle;
  long sn;
  pthread_t tid;
} thread_state_t;

static void *do_ (void *arg);
static void do__ (void *arg);

int
main (void)
{
  int rc;
  void *retval = (void *)0;
  thread_state_t state[N_THREAD];

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      state[i].sn = i + 1;
      state[i].idle = i;
      rc = pthread_create (&state[i].tid, NULL, do_, &state[i]);
      if (rc)
        {
          perror (NULL);
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (state[i].tid, (void **)&retval);
      if (rc)
        {
          perror (NULL);
        }
      assert (PTHREAD_CANCELED != retval
              && ((thread_state_t *)retval)->sn == state[i].sn);
    }

  return 0;
}

void *
do_ (void *arg)
{
  thread_state_t *state = (thread_state_t *)arg;
  fprintf (stderr, "> #%02li do_ %is ...\n", state->sn, state->idle);

  sleep (state->idle);
  do__ (state);

  fprintf (stderr, "< #%02li do_ exit\n", state->sn);

  switch (state->sn)
    {
    case 0:
    case 1:
    case 2:
      pthread_exit (state);
      break;                    /* unreachable */
    default:
      return state;
    }
}

void
do__ (void *arg)
{
  thread_state_t *state = (thread_state_t *)arg;
  fprintf (stderr, ">> #%02li, do__ %is ...\n", state->sn, state->idle);

  sleep (state->idle);

  if (1 == (state->sn & 1))
    {
      fprintf (stderr, "<< #%02li, do__ exit |\n", state->sn);
      pthread_exit (state);
    }
  else
    {
      fprintf (stderr, "<< #%02li, do__ exit ...\n", state->sn);
    }
}
