#include "_parallel_.h"
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N_THREADS 8

typedef struct thread_info_s
{
  pthread_t tid;
  long sn;
} thread_info_t;


void *
echo(void *arg)
{
	fprintf(stderr, "Hello, sn=%li\n", ((thread_info_t*) arg)->sn);
  return &(((thread_info_t*) arg)->sn);
}

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

  thread_info_t *tinfo = 0;
  tinfo = calloc(N_THREADS, sizeof(thread_info_t));
  if (!tinfo)
    {
      perror(0);
      return 1;
    }

	for (long i = 0; i < N_THREADS; i++)
    {
      fprintf(stdout, "creating thread %ld\n", i);
      tinfo[i].sn = i;
      int r = pthread_create(&tinfo[i].tid, 0, echo, &tinfo[i]);
      if (r)
        {
          perror("!panic, when create");
          goto clean_exit;
        }
    }

  void *retval;
  for (long i = 0; i < N_THREADS; i++)
    {
      int r = pthread_join(tinfo[i].tid, &retval);
      if (r)
        {
          perror("!panic, when join");
          continue;
        }
      fprintf(stderr, "tid=%li, return %li\n", tinfo[i].tid, *(long*) retval);
    }
  
 clean_exit:
  free(tinfo);
	
	return 0;
}
