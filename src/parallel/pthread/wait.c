#include <_parallel_.h>
#include <stdio.h>
#include <pthread.h>

#define N_THREAD 4
#define N_ERRSTR 128

typedef struct thread_state_s
{
  long sn;
} thread_state_t;

static int             opt_terminate = 0;
static int             has_produce   = 0;
static int             race_counter  = 0;
static pthread_mutex_t mutex;
static pthread_cond_t  cond;

void *consume(void *arg);
void *produce(void *arg);

void *
consume(void *arg)
{
  thread_state_t *state = (thread_state_t *) arg;
  int             rc;
  char            errstr[N_ERRSTR];

  fprintf(stderr, "> #%02li, consume\n", state->sn);

  while (opt_terminate)
    {
      fprintf(stderr, ">> #%02li, consume, locking ...\n", state->sn);
      rc = pthread_mutex_lock(&mutex);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, ">> !panic, #%02li, consume, lock",
                   state->sn);
          perror(errstr);
          goto exit;
        }
      fprintf(stderr, ">> #%02li, consume, locked\n", state->sn);

      while (has_produce == 0)
        {
          fprintf(stderr, ">>> #%02li, consume, waiting ...\n", state->sn);
          rc = pthread_cond_wait(&cond, &mutex);
          if (rc)
            {
              snprintf(errstr, N_ERRSTR, ">>> !panic, #%02li, consume, wait", state->sn);
              perror(errstr);
              goto exit_unlock;
            }
          fprintf(stderr, "<<< #%02li, consume, wait\n", state->sn);
        }
      has_produce = 0;
      ++race_counter;
      fprintf(stderr, "<< #%02li, consume, %04i", state->sn, race_counter);

    exit_unlock:
      fprintf(stderr, "<< #%02li, consume, unlocking ...\n", state->sn);
      rc = pthread_mutex_unlock(&mutex);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, "<< !panic, #%02li, consume, unlock", state->sn);
          perror(errstr);
          goto exit;
        }
      fprintf(stderr, "<< #%02li, consume, unlock\n", state->sn);
    }

 exit:
  fprintf(stderr, "< #%02li, consume\n", state->sn);
  return arg;
}

void *
produce(void *arg)
{
  thread_state_t *state = (thread_state_t *) arg;
  int             rc;
  char            errstr[N_ERRSTR];

  fprintf(stderr, "> #%02li, produce\n", state->sn);

  while (!opt_terminate)
    {
      fprintf(stderr, ">> #%02li, produce, lock ...\n", state->sn);
      rc = pthread_mutex_lock(&mutex);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, ">> #%02li, produce, lock", state->sn);
          perror(errstr);
          goto exit;
        }

      while (has_produce == 1)
        {
          fprintf(stderr, ">>> #%02li, produce, wait ...\n", state->sn);
          rc = pthread_cond_wait(&cond, &mutex);
          if (rc)
            {
              snprintf(errstr, N_ERRSTR, ">>> #%02li, produce, wait", state->sn);
              goto exit_unlock;
            }
        }
      has_produce = 1;
      ++race_counter;
      fprintf(stderr, "<<< #%02li, produce, "
              "opt_terminate=%02i, race_counter=%04i\n",
              state->sn,
              opt_terminate,
              race_counter);

    exit_unlock:
      rc = pthread_mutex_unlock(&mutex);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, "<< #%02li, produce, unlock", state->sn);
          perror(errstr);
          goto exit;
        }
      fprintf(stderr, "<< #%02li, produce, unlock\n", state->sn);
    }

 exit:
  fprintf(stderr, "< #%02li, produce\n", state->sn);
  return arg;
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  /* thread_state_t state[N_THREAD]; */
  /* pthread_t thread[N_THREAD]; */
  /* int rc; */

  /* /\* init mutex *\/ */
  /* rc = pthread_mutex_init(&mutex, 0); */
  /* if (rc) */
  /*   { */
  /*     perror("!panic, pthread_mutex_init"); */
  /*     return 1; */
  /*   } */

  /* /\* init cond *\/ */
  /* rc = pthread_cond_init(&cond, 0); */
  /* if (rc) */
  /*   { */
  /*     perror("!panic, pthread_cond_init"); */
  /*     return 1; */
  /*   } */

  /* /\* create one producer *\/ */
  /* state[0].sn = 0; */
  /* rc = pthread_create(&thread[0], 0, produce, &state[0]); */
  /* if (rc) */
  /*   { */
  /*     perror("!panic, create produce"); */
  /*     return 1; */
  /*   } */

  /* /\* create many consumers *\/ */
  /* for (long i = 1; i < N_THREAD; i++) */
  /*   { */
  /*     state[i].sn = i+1; */
  /*     rc = pthread_create(&thread[i], 0, consume, &state[i]); */
  /*     if (rc) */
  /*       { */
  /*         perror("!panic, create consumer"); */
  /*         return 1; */
  /*       } */
  /*   } */

  /* sleep(2); */
  /* opt_terminate = 1; */
  /* sleep(2); */

  /* /\* destroy cond *\/ */
  /* rc = pthread_cond_destroy(&cond); */
  /* if (rc) */
  /*   { */
  /*     perror("!panic, pthread_cond_destroy"); */
  /*   } */

  /* /\* destroy mutex *\/ */
  /* rc = pthread_mutex_destroy(&mutex); */
  /* if (rc) */
  /*   { */
  /*     perror("!panic, pthread_mutex_destroy"); */
  /*   } */

  return 0;
}
