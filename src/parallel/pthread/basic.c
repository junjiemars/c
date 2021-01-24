#include "_parallel_.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <assert.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  long      sn;
  pthread_t tid;
} thread_state_t;


void *
echo(void *arg)
{
  thread_state_t *state = (thread_state_t *) arg;

	fprintf(stderr, "> #%02li, Hello\n", state->sn);

  assert(state->tid == pthread_self() && "calling thread id");
  assert(pthread_equal(state->tid, pthread_self()) && "same as above");

  return &state->sn;
}

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

  thread_state_t  state[N_THREAD];
  void           *retval;
  int             rc;

  /* create threads */
	for (long i = 0; i < N_THREAD; i++)
    {
      fprintf(stdout, "+ creating thread #%02li\n", i);
      state[i].sn = i;
      rc = pthread_create(&state[i].tid, 0, echo, &state[i]);
      if (rc)
        {
          perror("!panic, pthread_create");
          return 1;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      fprintf(stderr, "- joining thread #%02li\n", i);
      rc = pthread_join(state[i].tid, &retval);
      if (rc)
        {
          perror("!panic, pthread_join");
          continue;
        }
      fprintf(stderr, "#%02li, tid=0x%016zx, return %li\n",
              state[i].sn,
              (long) state[i].tid,
              *(long*) retval);
    }

	return 0;
}
