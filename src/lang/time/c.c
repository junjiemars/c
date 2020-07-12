#include <_lang_.h>
#include <time.h>
#include <stdio.h>

void timer_reset(time_t *epoch);
void timer_wait(double secs);
double timer_elapsed(const time_t *epoch);

void
timer_reset(time_t *epoch) {
  *epoch = clock();
}

void
timer_wait(double secs) {
  clock_t end = clock() + (clock_t)(secs * CLOCKS_PER_SEC );
  while (clock() < end) {
    /* do nothing */
  }
}

double
timer_elapsed(const time_t *epoch) {
  double elapsed =  (double)(clock() - *epoch) / CLOCKS_PER_SEC;
  return elapsed;
}

int
main(int argc, char **argv) {
  if (argc < 2) {
    return 0;
  }

  long max;
  sscanf(argv[1], "%ld", &max);
  
  time_t epoch;
  timer_reset(&epoch);

  for (long i = 0; i < max; ++i) {
    /* do nothing */
  }
  double elapsed = timer_elapsed(&epoch);
  printf("elapsed: %lf secs\n", elapsed);

	return 0;
}
