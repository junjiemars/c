#include "_parallel_.h"
#include <stdio.h>
#include <pthread.h>

#if (DARWIN) || (LINUX)
#  include <unistd.h>
#elif (WINNT)
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#endif

#define N_SLEEP 2

void *sleep_routine(void *arg);

void*
sleep_routine(void *arg)
{
  fprintf(stderr, "sleep %i seconds ...\n", N_SLEEP);
  sleep(N_SLEEP);
  return arg;
}

int
main(int argc, char **argv) 
{
  _unused_(argc);
  _unused_(argv);
  
  pthread_t thread;
  int r = pthread_create(&thread, 0, sleep_routine, 0);
  if (r)
    {
      perror(0);
    }

  int exit_state = 0;
  pthread_exit(&exit_state);

  /* unreached code */
  fprintf(stderr, "pthread exit\n");

  return 0;
}
