#include <_cpu_.h>
#include "stdlib.h"
#include "stdio.h"
#include <time.h>

#define MAX (1024*1024*32)
#define REP 100
#define B  (16*1024)

char *array;

void
warmup(char *vec) {
  /* fit in L3 */
  for (int i = 0; i < MAX; i++) {
    vec[i] = 0;
  }
}

void
tiled(char *vec) {
  for (int i = 0; i < MAX; i += B) {
    for (int r = 0; r < REP; r++) {
      for (int j = i; j < (i + B); j+=64) {
        vec[j] = r;
      }
    }
  }
}

void
untiled(char *vec) {
  for (int r = 0; r < REP; r++) {
    for (int i = 0; i < MAX; i+=64) {
      vec[i] = r;
    }
  }
}

int
main() { 
  array = malloc(sizeof(char)*MAX);

  warmup(array);

  clock_t t1 = clock();
  tiled(array);

  clock_t t2 = clock();
  untiled(array);

  clock_t t3 = clock();
  printf ("tiled: %f sec\n", (double)(t2 - t1) / CLOCKS_PER_SEC);
  printf ("untiled: %f sec\n", (double)(t3 - t2) / CLOCKS_PER_SEC);
  
  /* to prevent optimizing out all the writes */
  printf ("array[0] = %d\n", array[0]);
  
  free(array);
  return 0;
}
