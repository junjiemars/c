#include <_parallel_.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  long sn;
} thread_state_t;

static pthread_mutex_t mutex;
static pthread_cond_t  cond;
static long            race_counter = N_THREAD;

void *race(void *arg);

void *
race(void *arg)
{
  thread_state_t *state = (thread_state_t *) arg;
  int             rc;

  fprintf(stderr, "> #%02li\n", state->sn);

  rc = pthread_mutex_lock(&mutex);
  if (rc)
    {
      perror("!panic, pthread_mutex_lock");
      goto exit;
    }

  sleep(1);
  fprintf(stderr, ">> #%02li, waiting ...\n", state->sn);

  rc = pthread_cond_wait(&cond, &mutex);
  if (rc)
    {
      perror("!panic, pthread_cond_wait");
      goto exit_lock;
    }

  sleep(1);
  --race_counter;
  fprintf(stderr, "<< #%02li, counter=%04li\n", state->sn, race_counter);

 exit_lock:
  rc = pthread_mutex_unlock(&mutex);
  if (rc)
    {
      perror("!panic, pthread_mutex_unlock");
    }
  fprintf(stderr, "<< #%02li\n", state->sn);
 exit:
  fprintf(stderr, "< #%02li\n", state->sn);
  return arg;
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  thread_state_t state[N_THREAD];
  pthread_t thread[N_THREAD];
  int rc;

  /* init mutex */
  rc = pthread_mutex_init(&mutex, 0);
  if (rc)
    {
      perror("!panic, pthread_mutex_init");
      return 1;
    }

  /* init cond */
  rc = pthread_cond_init(&cond, 0);
  if (rc)
    {
      perror("!panic, pthread_cond_init");
      return 1;
    }

  /* create threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      state[i].sn = i+1;
      rc = pthread_create(&thread[i], 0, race, &state[i]);
      if (rc)
        {
          perror("!panic, pthread_create");
          return 1;
        }
    }

  /* while (race_counter > 0) */
  /*   { */
  /*     sleep(1); */
  /*   } */
  /* sleep(2); */

  rc = pthread_cond_broadcast(&cond);
  if (rc)
    {
      perror("!panic, pthread_cond_signal");
      goto clean_exit;
    }

  /* /\* join threads *\/ */
  /* for (long i = 0; i < N_THREAD; i++) */
  /*   { */
  /*     rc = pthread_join(thread[i], 0); */
  /*     if (rc) */
  /*       { */
  /*         perror("!panic, pthread_join"); */
  /*       } */
  /*   } */

clean_exit:
  /* destroy cond */
  rc = pthread_cond_destroy(&cond);
  if (rc)
    {
      perror("!panic, pthread_cond_destroy");
    }

  /* destroy mutex */
  rc = pthread_mutex_destroy(&mutex);
  if (rc)
    {
      perror("!panic, pthread_mutex_destroy");
    }

  return 0;
}
