#include "_parallel_.h"
#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>

static atomic_int counter = 0;

static void *incr (void *);

int
main (int argc, char **argv)
{
  int n_thread = 2;
  pthread_t *threads;

  if (argc > 1)
    {
      sscanf (argv[1], "%d", &n_thread);
      if (n_thread < 0 || n_thread > 4)
        {
          n_thread = 2;
        }
    }

  threads = malloc (sizeof (pthread_t) * n_thread);
  if (threads == 0)
    {
      perror (0);
      exit (EXIT_FAILURE);
    }

  for (int i = 0; i < n_thread; i++)
    {
      if (pthread_create (&threads[i], 0, incr, &counter) < 0)
        {
          perror (0);
        }
    }

  for (int i = 0; i < n_thread; i++)
    {
      pthread_join (threads[i], 0);
    }
  free (threads);

  assert (counter == n_thread);

  return 0;
}

void *
incr (void *arg)
{
  atomic_fetch_add ((atomic_int *)arg, 1);
  return (atomic_int *)arg;
}
