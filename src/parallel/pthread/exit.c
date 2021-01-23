#include "_parallel_.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#if (DARWIN) || (LINUX)
#  include <unistd.h>
#elif (WINNT)
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#endif

#define N_THREAD 4

void *sleep_routine(void *arg);

void*
sleep_routine(void *arg)
{
  int *seconds = (int*) arg;
  fprintf(stderr, "> #%i sleep %i seconds ...\n", *seconds, *seconds);
  sleep(*seconds);
  fprintf(stderr, "< #%i exit ...\n", *seconds);
  return seconds;
}

int
main(int argc, char **argv) 
{
  _unused_(argc);
  _unused_(argv);
  
  pthread_t threads[N_THREAD];
  int states[N_THREAD];

  for (long i = 0; i < N_THREAD; i++)
    {
      states[i] = i;
      int r = pthread_create(&threads[i], 0, sleep_routine, &states[i]);
      if (r)
        {
          perror(0);
        }
    }

  pthread_exit(0);

  /* unreached code */
  fprintf(stderr, "pthread exit\n");

  return 0;
}
