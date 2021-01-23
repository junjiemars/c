#include <_parallel_.h>
#include <pthread.h>
#include <stdio.h>

#define N_THREAD 4

typedef struct thread_state_s
{
  long           sn;
  pthread_t      tid;
  pthread_attr_t attr;
  int            detached;
} thread_state_t;

void is_detached(int state, long sn);
void *detached_routine(void *arg);


void
is_detached(int state, long sn)
{
  pthread_t tid = pthread_self();
  switch (state)
    {
    case PTHREAD_CREATE_DETACHED:
      fprintf(stderr, "#%02li, tid=0x%016zx, PTHREAD_CREATE_DETACHED\n",
              sn, (long) tid);
      break;
    case PTHREAD_CREATE_JOINABLE:
      fprintf(stderr, "#%02li, tid=0x%016zx, PTHREAD_CREATE_JOINABLE\n",
              sn, (long) tid);
      break;
    default:
      fprintf(stderr, "#%02li, tid=0x%016zx, %i (unknown)\n",
              sn, (long) tid, state);
      break;
    }
}

void *
detached_routine(void *arg)
{
  thread_state_t *state;
  int             rc;
  int             detached;
  state = (thread_state_t *) arg;
  rc = pthread_attr_getdetachstate(&state->attr, &detached);
  if (rc)
    {
      perror("!panic, detached_routine");
    }
  else
    {
      is_detached(detached, state->sn);
    }
  return state;
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  pthread_attr_t attr;
  int            detach;
  int            rc;
  thread_state_t states[N_THREAD];

  /* check main thread is detached */
  rc = pthread_attr_init(&attr);
  if (rc)
    {
      perror("!panic, pthread_attr_init");
      return 1;
    }
  rc = pthread_attr_getdetachstate(&attr, &detach);
  if (rc)
    {
      perror("!panic, pthread_attr_getdetachstate");
      return 1;
    }
  is_detached(detach, 0);
  rc = pthread_attr_destroy(&attr);
  if (rc)
    {
      perror("!panic, pthread_attr_destroy");
      return 1;
    }

  /* create joinable and detached threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      rc = pthread_attr_init(&states[i].attr);
      if (rc)
        {
          perror("!panic, pthread_attr_init");
          return 1;
        }

      states[i].sn = i+1;
      states[i].detached = (1 == (i & 1))
        ? PTHREAD_CREATE_JOINABLE : PTHREAD_CREATE_DETACHED;

      rc = pthread_attr_setdetachstate(&states[i].attr, states[i].detached);
      if (rc)
        {
          perror("!panic, pthread_attr_setdetachstate");
          return 1;
        }

      rc = pthread_create(&states[i].tid,
                         &states[i].attr,
                         detached_routine,
                         &states[i]);
      if (rc)
        {
          perror("!panic, pthread_create");
          return 1;
        }
    }

  /* join joinable threads */
  for (long i = 0; i < N_THREAD; i++)
    {
      if (PTHREAD_CREATE_JOINABLE == states[i].detached)
        {
          rc = pthread_join(states[i].tid, 0);
          if (rc)
            {
              perror("!panic, pthread_join");
            }
        }
      rc = pthread_attr_destroy(&states[i].attr);
      if (rc)
        {
          perror("!panic, pthread_attr_destroy");
        }
    }

  return 0;
}
