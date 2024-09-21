#include "_parallel_.h"
#include <pthread.h>

/*
 * 1. `pthread_t' is an opaque type as the identifer of thread.
 * 2. so `pthread_equal' exists because 1st.
 *
 */

#define N_THREAD 4

typedef struct thread_state_s
{
  long sn;
  pthread_t tid;
  int data;
} thread_state_s;

void *
echo (void *arg)
{
  thread_state_s *state = (thread_state_s *)arg;

  fprintf (stderr, "> #%02li, Hello\n", state->sn);

  assert (pthread_equal (state->tid, pthread_self ()) && "same thread");

  state->data = random ();
  sleep (1);

  return &state->sn;
}

int
main (void)
{
  thread_state_s state[N_THREAD];
  void *retval;
  int rc;

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      fprintf (stderr, "+ creating thread #%02li ...\n", i);
      state[i].sn = i;
      rc = pthread_create (&state[i].tid, NULL, echo, &state[i]);
      if (rc)
        {
          perror ("!panic, pthread_create");
          return 1;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      fprintf (stderr, "- joining thread #%02li ...\n", i);
      rc = pthread_join (state[i].tid, &retval);
      if (rc)
        {
          perror ("!panic, pthread_join");
          continue;
        }
      fprintf (stderr, "< #%02li, tid=0x%016zx, return %li\n", state[i].sn,
               (long)state[i].tid, *(long *)retval);
    }

  return 0;
}
