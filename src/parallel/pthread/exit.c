#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4
#define _cancel_(x) ((x) == (N_THREAD - 1))
#define _cleanup_(x) ((x) == (N_THREAD - 2))

typedef struct thread_state_s
{
  unsigned int idle;
  long sn;
  pthread_t tid;
} thread_state_t;

static void *do_ (void *);
static void do__ (void *);
static void cleanup_ (void *);

int
main (void)
{
  int rc;
  long retval;
  thread_state_t state[N_THREAD];

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      state[i].sn = i;
      state[i].idle = i + 1;
      rc = pthread_create (&state[i].tid, NULL, do_, &state[i]);
      if (rc)
        {
          perror (NULL);
          exit (EXIT_FAILURE);
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      if (_cancel_ (i))
        {
          rc = pthread_cancel (state[i].tid);
          if (rc)
            {
              perror (NULL);
              exit (EXIT_FAILURE);
            }
          fprintf (stderr, "#%02li canceled.\n", state[i].sn);
        }
      else
        {
          rc = pthread_join (state[i].tid, (void **)&retval);
          if (rc)
            {
              perror (NULL);
              exit (EXIT_FAILURE);
            }
          else
            {
              assert (state[i].sn == (long)retval);
              fprintf (stderr, "#%02li exit code %02li.\n", state[i].sn,
                       retval);
            }
        }
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

  if (_cleanup_ (state->sn))
    {
      /* whip the ass: should be used paired */
      pthread_cleanup_push (cleanup_, state);
      pthread_cleanup_pop (1);
    }

  fprintf (stderr, "< #%02li do_ exit\n", state->sn);

  return (void *)state->sn;
}

void
do__ (void *arg)
{
  thread_state_t *state = (thread_state_t *)arg;
  fprintf (stderr, ">> #%02li do__ %is ...\n", state->sn, state->idle);

  sleep (state->idle);

  if (1 == (state->sn & 1))
    {
      fprintf (stderr, "<< #%02li do__ exit |\n", state->sn);
      pthread_exit ((void *)state->sn);
    }
  else
    {
      fprintf (stderr, "<< #%02li do__ exit ||\n", state->sn);
    }
}

void
cleanup_ (void *arg)
{
  thread_state_t *state = (thread_state_t *)arg;
  fprintf (stderr, "_:_ #%02li cleanup ...\n", state->sn);
}
