#include "_parallel_.h"
#include <pthread.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  long sn;
  int *data;
} thread_state_s;

static pthread_key_t thread_key;

static void *roll (void *);
static void destructor (void *);

int
main (void)
{
  int rc;
  int *data = 0;
  pthread_t thread[N_THREAD];
  thread_state_s state[N_THREAD];

  /* alloc data */
  data = malloc (sizeof (*data) * N_THREAD);
  if (!data)
    {
      perror ("!panic, malloc");
      return 1;
    }

  /* create key */
  rc = pthread_key_create (&thread_key, destructor);
  if (rc)
    {
      perror ("!panic, pthread_key_create");
      goto clean_exit;
    }

  /* create thread */
  for (long i = 0; i < N_THREAD; i++)
    {
      state[i].sn = i + 1;
      state[i].data = data;
      rc = pthread_create (&thread[i], 0, roll, &state[i]);
      if (rc)
        {
          perror ("!panic, pthread_create");
          goto clean_key;
        }
    }

  sleep (1);

  /* join thread */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_join (thread[i], 0);
      if (rc)
        {
          perror ("!panic, pthread_join");
        }
    }

clean_key:
  rc = pthread_key_delete (thread_key);
  if (rc)
    {
      perror ("!panic, pthread_key_delete");
    }

clean_exit:
  free (data);

  return 0;
}

void *
roll (void *arg)
{
  thread_state_s *state = (thread_state_s *)arg;
  fprintf (stderr, "#%02li\n", state->sn);
  sleep (1);
  return arg;
}

void
destructor (void *arg)
{
  thread_state_s *state = (thread_state_s *)arg;
  fprintf (stderr, "#%02li, destructor\n", state->sn);
  free (state->data);
}
