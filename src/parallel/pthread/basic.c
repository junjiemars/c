#include "_parallel_.h"
#include <limits.h>
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

static void print_limits ();
static void *echo (void *);

int
main (void)
{
  thread_state_s state[N_THREAD];
  void *retval;
  int rc;

  print_limits ();

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
  fprintf (stderr, "#main, tid=0x%0zx\n", (size_t)pthread_self ());
  for (long i = 0; i < N_THREAD; i++)
    {
      fprintf (stderr, "- joining thread #%02li ...\n", i);
      rc = pthread_join (state[i].tid, &retval);
      if (rc)
        {
          perror ("!panic, pthread_join");
          continue;
        }
      fprintf (stderr, "< #%02li, tid=0x%0zx, return %li\n", state[i].sn,
               (size_t)state[i].tid, *(long *)retval);
    }

  return 0;
}

void
print_limits ()
{
  long rc;
#ifdef PTHREAD_DESTRUCTOR_ITERATIONS
  /*
   * maximum number of times an implementation will try to destory the
   * thread-specific data when a thread exits
   */
  printf ("# %s %zu\n", _str_ (PTHREAD_DESTRUCTOR_ITERATIONS),
          (size_t)PTHREAD_DESTRUCTOR_ITERATIONS);
#elif defined(_SC_THREAD_DESTRUCTOR_ITERATIONS)
  rc = sysconf (_SC_THREAD_DESTRUCTOR_ITERATIONS);
  if (rc == -1)
    {
      printf ("# %s %zu\n", _str_ (_SC_THREAD_DESTRUCTOR_ITERATIONS),
              (size_t)_SC_THREAD_DESTRUCTOR_ITERATIONS);
    }
  else
    {
      printf ("# %s (unkonwn)\n", _str_ (_SC_THREAD_DESTRUCTOR_ITERATIONS));
    }
#else
  printf ("# %s (unkonwn)\n", _str_ (PTHREAD_DESTRUCTOR_ITERATIONS));
#endif
#ifdef PTHREAD_KEYS_MAX
  printf ("# %s %zu\n", _str_ (PTHREAD_KEYS_MAX), (size_t)PTHREAD_KEYS_MAX);
#elif defined(_SC_THREAD_KEYS_MAX)
  rc = sycconf ()
#else
  printf ("# %s (no limit)\n", _str_ (PTHREAD_KEYS_MAX));
#endif
#ifdef PTHREAD_STACK_MIN
  printf ("# %s %zu (bytes)\n", _str_ (PTHREAD_STACK_MIN),
          (size_t)PTHREAD_STACK_MIN);
#elif defined(_SC_THREAD_STACK_MIN)
      rc
      = sysconf (_SC_THREAD_STACK_MIN);
  if (rc == -1)
    {
      printf ("# %s (no limit)\n", _str_ (_SC_THREAD_STACK_MIN));
    }
  else
    {
      printf ("# %s %zu (bytes)\n", _str_ (_SC_THREAD_STACK_MIN),
              (size_t)_SC_THREAD_STACK_MIN);
    }
#else
  printf ("# %s (no limit)\n", _str_ (PTHREAD_STACK_MIN));
#endif
#ifdef PTHREAD_THREADS_MAX
  printf ("# %s %zu\n", _str_ (PTHREAD_THREADS_MAX),
          (size_t)PTHREAD_THREADS_MAX);
#elif defined(_SC_THREAD_THREADS_MAX)
  rc = sysconf (_SC_THREAD_THREADS_MAX);
  if (rc == -1)
    {
      printf ("# %s (no limit)\n", _str_ (_SC_THREAD_THREADS_MAX));
    }
  else
    {
      printf ("# %s %zu\n", _str_ (_SC_THREAD_THREADS_MAX),
              (size_t)_SC_THREAD_THREADS_MAX);
    }
#else
  printf ("# %s (no limit)\n", _str_ (PTHREAD_THREADS_MAX));
#endif
}

void *
echo (void *arg)
{
  thread_state_s *state = (thread_state_s *)arg;

  fprintf (stderr, "> #%02li, Hello\n", state->sn);

  assert (pthread_equal (state->tid, pthread_self ()) && "same thread");

  state->data = random ();
  sleep (1);

  /* same as return &state->sn; */
  pthread_exit (&state->sn);
}
