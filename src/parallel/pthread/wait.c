#include <_parallel_.h>
#include <stdio.h>
#include <pthread.h>
#include <errno.h>

#define N_CONSUMER 4
#define N_PRODUCER 2
#define N_ERRSTR   128
#define QSIZE      2

typedef struct thread_state_s
{
  long            sn;
} thread_state_t;

static int             opt_terminate = 0;
static pthread_mutex_t mutex;
static pthread_cond_t  less, more;
static int             queue[QSIZE];
static int             next_in, next_out;
static int             occupied;
static int             alphabet;

void *consume(void *arg);
void *produce(void *arg);

void *
consume(void *arg)
{
  thread_state_t *state = (thread_state_t *) arg;
  int             rc;
  char            errstr[N_ERRSTR];
  char            item;

  while (1)
    {
      rc = pthread_mutex_lock(&mutex);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, "--- !panic, #%02li, lock\n", state->sn);
          perror(errstr);
          goto exit;
        }

      while (occupied <= 0)
        {
          rc = pthread_cond_wait(&more, &mutex);
          if (rc)
            {
              snprintf(errstr, N_ERRSTR, "--- !panic, #%02li, wait", state->sn);
              perror(errstr);
              goto exit_unlock;
            }
        }
      item = queue[next_out++];
      next_out %= QSIZE;
      occupied--;
      fprintf(stderr, "--- #%02li, consume: %c\n", state->sn, item);

      rc = pthread_cond_signal(&less);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, "--- !panic, #%02li, consumer", state->sn);
          perror(errstr);
        }

    exit_unlock:
      rc = pthread_mutex_unlock(&mutex);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, "--- !panic, #%02li, unlock", state->sn);
          perror(errstr);
          goto exit;
        }

      if (opt_terminate)
        {
          goto exit;
        }
      sleep(1);
    }

 exit:
  return arg;
}

void *
produce(void *arg)
{
  thread_state_t *state = (thread_state_t *) arg;
  int             rc;
  char            errstr[N_ERRSTR];
  char            item;

  while (1)
    {
      rc = pthread_mutex_lock(&mutex);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, "+++ !panic, #%02li, lock", state->sn);
          perror(errstr);
          goto exit;
        }

      while (occupied >= QSIZE)
        {
          fprintf(stderr, "+++ #%02li ...\n", state->sn);
          rc = pthread_cond_wait(&less, &mutex);
          if (rc)
            {
              snprintf(errstr, N_ERRSTR, "+++ !panic, #%02li, wait", state->sn);
              goto exit_unlock;
            }
        }

      item = (alphabet++ % 26) + 'A';
      queue[next_in++] = item;
      next_in %= QSIZE;
      occupied++;
      fprintf(stderr, "+++ #%02li, produce: %c\n", state->sn, item);

      rc = pthread_cond_signal(&more);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, "+++ !panic, #%02li, signal", state->sn);
          perror(errstr);
        }

    exit_unlock:
      rc = pthread_mutex_unlock(&mutex);
      if (rc)
        {
          snprintf(errstr, N_ERRSTR, "+++ !panic, #%02li, unlock", state->sn);
          perror(errstr);
          goto exit;
        }

      if (opt_terminate)
        {
          goto exit;
        }
    }

 exit:
  return arg;
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  thread_state_t consumer_state[N_CONSUMER];
  thread_state_t producer_state[N_CONSUMER];
  pthread_t      consumer[N_CONSUMER];
  pthread_t      producer[N_PRODUCER];
  int            rc;

  /* init mutex */
  rc = pthread_mutex_init(&mutex, 0);
  if (rc)
    {
      perror("!panic, pthread_mutex_init");
      return 1;
    }

  /* init cond */
  rc = pthread_cond_init(&less, 0);
  if (rc)
    {
      perror("!panic, pthread_cond_init, less");
      return 1;
    }
  rc = pthread_cond_init(&more, 0);
  if (rc)
    {
      perror("!panic, pthread_cond_init, more");
      return 1;
    }

  /* create many consumers */
  for (long i = 1; i < N_CONSUMER; i++)
    {
      consumer_state[i].sn = i+10;
      rc = pthread_create(&consumer[i], 0, consume, &consumer_state[i]);
      if (rc)
        {
          perror("!panic, create consumer");
          return 1;
        }
    }

  /* create producer */
  for (long i = 0; i < N_PRODUCER; i++)
    {
      producer_state[i].sn = i;
      rc = pthread_create(&producer[i], 0, produce, &producer_state[i]);
      if (rc)
        {
          perror("!panic, create produce");
          return 1;
        }
    }

  /* terminate */
  sleep(1);
  opt_terminate = 1;
  sleep(1);

  /* destroy cond */
  rc = pthread_cond_destroy(&more);
  if (rc)
    {
      perror("!panic, pthread_cond_destroy, more");
    }
  rc = pthread_cond_destroy(&less);
  if (rc)
    {
      perror("!panic, pthread_cond_destroy, less");
    }

  /* destroy mutex */
  rc = pthread_mutex_destroy(&mutex);
  if (rc)
    {
      perror("!panic, pthread_mutex_destroy");
    }

  return 0;
}
