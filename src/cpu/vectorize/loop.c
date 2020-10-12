#include <_cpu_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define ROW_SIZE (NM_LOOP_VECTOR_WIDTH * 16)
#define COL_SIZE (NM_LOOP_VECTOR_WIDTH * 16)

#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

#define X 0x11

void print_time(char *const what, long elpased);
void raw(char *const table, int row_size, int col_size);
void vectorize(char *const table, int row_size, int col_size);
int validate(const char *a, const char *b);
void test_raw(char *const table);
void test_vectorize(char *const table);

void
print_time(char *const what, long elapsed) {
  printf("%16s, escaped %8li cpu time, %16lf sec\n",
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
vectorize(char *const table, int row_size, int col_size) {
  for (int i = 0; i < row_size; i+=NM_LOOP_VECTOR_WIDTH) {
    for (int j = 0; j < col_size; j+=NM_LOOP_VECTOR_WIDTH) {
     table[i*j+j] = X; 
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
test_vectorize(char *const table) {
  clock_t elapsed;
  _time_(vectorize(table, ROW_SIZE, COL_SIZE), elapsed);
  print_time("vectorize", elapsed);
}

int
main(void) { 
  size_t size = sizeof(char) * ROW_SIZE * COL_SIZE;
  char *vectorize = calloc(1, size);
  char *raw = calloc(1, size);
  char *vectorize1 = calloc(1, size);

  test_vectorize(vectorize);
  test_raw(raw);
  test_vectorize(vectorize1);
  
  printf("validate(raw, vectorize): %s\n",
         validate(raw, vectorize) ? "false" : "true");

  free(raw);
  free(vectorize);
  free(vectorize1);

  return 0;
}
