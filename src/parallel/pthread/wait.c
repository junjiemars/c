#include <_parallel_.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  long sn;
} thread_state_t;

void *race(void *arg);

static pthread_mutex_t mutex;
static pthread_cond_t  cond;

void *
race(void *arg)
{
  
  return arg;
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  int rc;

  rc = pthread_mutex_init(&mutex, 0);
  if (rc)
    {
      perror("!panic, pthread_mutex_init");
      return 1;
    }

  rc = pthread_cond_init(&cond, 0);
  if (rc)
    {
      perror("!panic, pthread_cond_init");
      return 1;
    }

  rc = pthread_cond_destroy(&cond);
  if (rc)
    {
      perror("!panic, pthread_cond_destroy");
    }

  rc = pthread_mutex_destroy(&mutex);
  if (rc)
    {
      perror("!panic, pthread_mutex_destroy");
    }

  return 0;
}
