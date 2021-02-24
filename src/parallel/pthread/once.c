#include <_parallel_.h>
#include <pthread.h>
#include <stdio.h>
#include <assert.h>

#define N_THREAD 4

static int count;

static void init_routine(void);


void
init_routine(void)
{
  pthread_t tid;
  ++count;

  tid = pthread_self();
  fprintf(stderr, "#%02li, count = %i\n", (long) tid, count);
}

int
main(int argc, char **argv)
{
  pthread_once_t once = PTHREAD_ONCE_INIT;
  int            rc;

  _unused_(argc);
  _unused_(argv);

  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_once(&once, init_routine);
      if (rc)
        {
          perror(NULL);
        }
    }
  ASSERT(count == 1 && "init just only once");

  return 0;
}
