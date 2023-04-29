#include "_process_.h"


unsigned long long  count  =  0;

static void  check_time(const char*, struct timeval*, unsigned long long);


int
main(int argc, char *argv[])
{
  int              n;
  pid_t            pid;
  char            *s;
  long             timeout;
  struct timeval   end;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <nice> [interval]\n");
      exit(1);
    }
  n = strtol(argv[1], NULL, 10);
  if (gettimeofday(&end, NULL) == -1)
    {
      perror(NULL);
      exit(1);
    }
  timeout = 10;
  if (argc > 2)
    {
      timeout = strtol(argv[2], NULL, 10);
    }
  end.tv_sec += timeout;
  printf("NZERO = %d, current nice = %d, timeout = %lis\n",
         NZERO, nice(0) + NZERO, timeout);

  setbuf(stdout, NULL);

  if ((pid = fork()) == -1)
    {
      perror(NULL);
      exit(1);
    }
  else if (pid == 0)
    {
      s = "child";
      printf("%6s nice = %d, adjusting by %2d\n", s, nice(0) + NZERO, n);
      errno = 0;
      if (nice(n) == -1 && errno != 0)
        {
          perror(NULL);
          exit(1);
        }
    }
  else
    {
      s = "parent";
      printf("%6s nice = %2d\n", s, nice(0) + NZERO);
    }

  for (;;)
    {
      if (++count == 0)
        {
          printf("!%s count out\n", s);
          exit(0);
        }
      check_time(s, &end, count);
    }

  exit(0);
}

void
check_time(const char *s, struct timeval *end, unsigned long long count)
{
  struct timeval  cur;

  if (gettimeofday(&cur, NULL) == -1)
    {
      perror(NULL);
      exit(1);
    }

  if (cur.tv_sec >= end->tv_sec && cur.tv_usec >= end->tv_usec)
    {
      printf("!%6s timeout: count = %020llu, nice = %2d\n",
             s, count, nice(0) + NZERO);
      exit(0);
    }
}
