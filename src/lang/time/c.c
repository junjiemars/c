#include <_lang_.h>
#include <time.h>
#include <stdio.h>

void timer_reset(clock_t *epoch);
void timer_wait(double secs);
double timer_elapsed(const clock_t *epoch);

void
timer_reset(clock_t *epoch) 
{
  *epoch = clock();
  if ((clock_t) -1 == *epoch)
    {
      perror(0);
    }
}

void
timer_wait(double secs) 
{
  clock_t end = clock() + (clock_t)(secs * CLOCKS_PER_SEC );
  while (clock() < end) 
    {
      /* do nothing */
    }
}

double
timer_elapsed(const clock_t *epoch) 
{
  double elapsed =  (double) (clock() - *epoch) / CLOCKS_PER_SEC;
  return elapsed;
}

int
main(int argc, char **argv) 
{
  if (argc < 2) 
    {
      printf("!please, input the max waiting seconds.\n");
      return 1;
    }

  long max;
  sscanf(argv[1], "%ld", &max);
  
  clock_t epoch;
  timer_reset(&epoch);

  for (long i = 0; i < max; ++i) 
    {
      /* do nothig */
    }
  double elapsed = timer_elapsed(&epoch);
  printf("elapsed: %lf secs\n", elapsed);

	return 0;
}
