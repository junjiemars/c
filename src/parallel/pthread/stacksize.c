#include "_parallel_.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#if (DARWIN) || (LINUX)
#  include <unistd.h>
#  include <limits.h>
#elif (WINNT)
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#endif

#define N_THREAD 4

typedef struct thread_state_s
{
  long sn;
  pthread_attr_t attr;
} thread_state_t;

void *check_stacksize(void *arg);

void*
check_stacksize(void *arg)
{
  thread_state_t *state = (thread_state_t*) arg;
  size_t stacksize;
  int r = pthread_attr_getstacksize(&state->attr, &stacksize);
  if (r)
    {
      perror("!panic, check_stacksize");
    }
  fprintf(stderr, "#%02li, tid = 0x%016zx, stacksize = 0x%08zx\n",
          state->sn,
          (long) pthread_self(),
          stacksize);
  return state;
}

int
main(int argc, char **argv) 
{
  _unused_(argc);
  _unused_(argv);
  
  pthread_t threads[N_THREAD];
  thread_state_t states[N_THREAD];
  pthread_attr_t attr;
  size_t stacksize;
  int r;

  /* check default stacksize */
  r = pthread_attr_init(&attr);
  if (r)
    {
      perror(0);
      return 1;
    }
  r = pthread_attr_getstacksize(&attr, &stacksize);
  if (r)
    {
      perror("!panic, pthread_attr_getstacksize");
      return 1;
    }
  fprintf(stderr, "#00, tid = 0x%016zx, stacksize = 0x%08zx\n",
          (long) pthread_self(),
          stacksize);
  r = pthread_attr_destroy(&attr);
  if (r)
    {
      perror("!panic, pthread_attr_destroy");
      return 1;
    }
  
  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      stacksize = PTHREAD_STACK_MIN * (i+1);
      r = pthread_attr_init(&states[i].attr);
      if (r)
        {
          perror("!panic, pthread_attr_init");
          return 1;
        }
      r = pthread_attr_setstacksize(&states[i].attr, stacksize);
      if (r)
        {
          perror("!panic, pthread_attr_setstacksize");
          return 1;
        }

      states[i].sn = i+1;
      r = pthread_create(&threads[i], &states[i].attr, check_stacksize, &states[i]);
      if (r)
        {
          perror("!panic, pthread_create");
          return 1;
        }
    }

  /* join threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      r = pthread_join(threads[i], 0);
      if (r)
        {
          perror("!panic, pthread_join");
        }
      r = pthread_attr_destroy(&states[i].attr);
      if (r)
        {
          perror("!panic, pthread_attr_destroy");
        }
    }

  return 0;
}
