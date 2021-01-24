#include "_parallel_.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  unsigned int idle;
  long         sn;
  pthread_t    tid;
} thread_state_t;

void *do_(void *arg);
void do__(void *arg);

void *
do_(void *arg)
{
  thread_state_t *state = (thread_state_t *) arg;
  fprintf(stderr, "> #%02li do_ %is ...\n",
          state->sn,
          state->idle);

  sleep(state->idle);
  do__(state);

  fprintf(stderr, "< #%02li do_ exit\n", state->sn);

  pthread_exit(arg);
}

void
do__(void *arg)
{
  thread_state_t *state = (thread_state_t *) arg;
  fprintf(stderr, ">> #%02li, do__ %is ...\n",
          state->sn,
          state->idle);

  sleep(state->idle);

  if (1 == (state->sn & 1))
    {
      fprintf(stderr, "<< #%02li, do__ exit |\n", state->sn);
      pthread_exit(state);
    }
  else
    {
      fprintf(stderr, "<< #%02li, do__ exit ...\n", state->sn);
    }
}


int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  thread_state_t state[N_THREAD];
  int            rc;

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      state[i].sn = i+1;
      state[i].idle = i;
      rc = pthread_create(&state[i].tid, 0, do_, &state[i]);
      if (rc)
        {
          perror(0);
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join(state[i].tid, 0);
      if (rc)
        {
          perror(0);
        }
    }

  return 0;
}
