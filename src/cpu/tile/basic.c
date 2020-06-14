#include <_cpu_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW_SIZE 1024
#define COL_SIZE 1024

#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define X 0x11

char *table_a, *table_b;

void
raw(char *table) {
  for (int i = 0; i < ROW_SIZE; i++) {
    for (int j = 0; j < COL_SIZE; j++) {
      table[i*j+j] = X;
    }
  }
}

void
tile(char *table) {
  for (int i = 0; i < ROW_SIZE; i+=NM_CPU_CACHE_LINE) {
    for (int j = 0; j < COL_SIZE; j+=NM_CPU_CACHE_LINE) {
      
      for (int k = j; k < MIN(j+NM_CPU_CACHE_LINE, COL_SIZE); k++) {
        for (int l = i; l < MIN(i+NM_CPU_CACHE_LINE, ROW_SIZE); l++) {
          table[l*k+k] = X;
        }
      }
    }
  }
}

int
validate(const char *a, const char *b) {
  int i = 0;
  for (int i = 0; i < ROW_SIZE; i++) {
    for (int j = 0; j < COL_SIZE; j++) {
      if (a[i*j+j] != b[i*j+j]) {
        i = 1;
        goto clean_exit;
      }
    }
  }
 clean_exit:
  return i;
}

int
main() { 
  clock_t elapsed;

  /* raw */
  table_a = malloc(sizeof(char) * (ROW_SIZE*COL_SIZE));
  memset(table_a, 0, ROW_SIZE * COL_SIZE);

  _time_(raw(table_a), elapsed);
  printf("raw, escaped %li cpu time, %lf sec\n",
         elapsed, (double)elapsed/CLOCKS_PER_SEC);
  
  /* tile */
  table_b = malloc(sizeof(char) * (ROW_SIZE*COL_SIZE));
  memset(table_b, 0, ROW_SIZE * COL_SIZE);

  _time_(tile(table_b), elapsed);
  printf("tile, escaped %li cpu time, %lf sec\n",
         elapsed, (double)elapsed/CLOCKS_PER_SEC);

  /* raw */
  _time_(raw(table_a), elapsed);
  printf("raw, escaped %li cpu time, %lf sec\n",
         elapsed, (double)elapsed/CLOCKS_PER_SEC);
  
  printf("validate(raw, tile): %s\n",
         validate(table_a, table_b) ? "false" : "true");
  free(table_a);
  free(table_b);

  return 0;
}
