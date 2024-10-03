#include "_parallel_.h"
#include <pthread.h>

#define N_CONSUMER 2
#define N_PRODUCER 2
#define N_SLEEP 1

typedef struct thread_state_s
{
  int sn;
  struct thread_state_s *next;
} thread_state_t;

static void *consume (void *);
static void *produce (void *);

static int qexit = 0;
static thread_state_t *qstate;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int
main (void)
{
  pthread_t consumer[N_CONSUMER];
  pthread_t producer[N_PRODUCER];
  thread_state_t *state;

  for (int i = 0; i < N_CONSUMER; i++)
    {
      pthread_create (&consumer[i], NULL, consume, (void *)&i);
    }

  for (int i = 0; i < N_PRODUCER; i++)
    {
      state = malloc (sizeof (thread_state_t));
      state->sn = i;
      pthread_create (&producer[i], NULL, produce, state);
    }

  sleep (N_SLEEP);

  for (int i = 0; i < N_PRODUCER; i++)
    {
      pthread_join (producer[i], NULL);
    }
  qexit++;

  for (int i = 0; i < N_CONSUMER; i++)
    {
      pthread_join (consumer[i], NULL);
    }

  pthread_mutex_destroy (&mutex);
  pthread_cond_destroy (&cond);

  return 0;
}

void *
consume (__attribute__ ((unused)) void *arg)
{
  thread_state_t *s;
  pthread_t tid = pthread_self ();

  for (;;)
    {
      pthread_mutex_lock (&mutex);
      if (qexit)
        {
          fprintf (stderr, "# tid=%p %s exiting ...\n", tid, __FUNCTION__);
          break;
        }
      while (qstate == NULL)
        {
          pthread_cond_wait (&cond, &mutex);
        }
      s = qstate;
      qstate = s->next;
      pthread_mutex_unlock (&mutex);
      fprintf (stderr, "# tid=%p %s sn=%02i\n", tid, __FUNCTION__, s->sn);
      free (s);
    }
  return (void *)0;
}

void *
produce (__attribute__ ((unused)) void *arg)
{
  thread_state_t *s;
  pthread_t tid = pthread_self ();

  for (;;)
    {
      pthread_mutex_lock (&mutex);
      if (qexit)
        {
          fprintf (stderr, "# tid=%p %s exiting ...\n", tid, __FUNCTION__);
          break;
        }
      s = malloc (sizeof (thread_state_t));
      s->next = qstate;
      qstate = s;
      pthread_mutex_unlock (&mutex);
      fprintf (stderr, "# tid=%p %s sn=%02i\n", tid, __FUNCTION__, s->sn);
      pthread_cond_signal (&cond);
    }

  return (void *)0;
}
