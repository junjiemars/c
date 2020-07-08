#include <_cpu_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ROW_SIZE (NM_CPU_CACHE_LINE * 16)
#define COL_SIZE (NM_CPU_CACHE_LINE * 16)

#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define X 0x11

void
print_time(char *const what, long elapsed) {
  printf("%8s, escaped %8li cpu time, %16lf sec\n",
         what, elapsed, (double)elapsed/CLOCKS_PER_SEC);
}

void
raw(char *const table, int row_size, int col_size) {
  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < col_size; j++) {
      table[i*j+j] = X;
    }
  }
}

void
tile(char *const table, int row_size, int col_size) {
  for (int i = 0; i < row_size; i+=NM_CPU_CACHE_LINE) {
    for (int j = 0; j < col_size; j+=NM_CPU_CACHE_LINE) {
      
      for (int k = j; k < MIN(j+NM_CPU_CACHE_LINE, col_size); k++) {
        for (int l = i; l < MIN(i+NM_CPU_CACHE_LINE, row_size); l++) {
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

void
test_raw(char *const table) {
  clock_t elapsed;
  _time_(raw(table, ROW_SIZE, COL_SIZE), elapsed);
  print_time("raw", elapsed);
}

void
test_tile(char *const table) {
  clock_t elapsed;
  _time_(tile(table, ROW_SIZE, COL_SIZE), elapsed);
  print_time("tile", elapsed);
}

int
main(void) { 
  size_t size = sizeof(char) * ROW_SIZE * COL_SIZE;
  char *tile = calloc(1, size);
  char *raw = calloc(1, size);
  char *tile1 = calloc(1, size);

  test_tile(tile);
  test_raw(raw);
  test_tile(tile1);
  
  printf("validate(raw, tile): %s\n",
         validate(raw, tile) ? "false" : "true");

  free(raw);
  free(tile);
  free(tile1);

  return 0;
}
