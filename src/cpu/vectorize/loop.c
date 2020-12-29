#include <_cpu_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define ROW_SIZE (NM_LOOP_VECTOR_WIDTH * 1024)

#define MAX(a, b) (((a) < (b)) ? (b) : (a))
#define MIN(a, b) (((a) < (b)) ? (a) : (b))


void print_time(char *const what, long elpased);
void fill(int *const array, int row_size);
void raw(int *const dst, int *const src, int row_size);
void vectorize(int *const dst, int *const src, int row_size);
int validate(int *const a, int *const b, int row_size);
void test_fill(int *const dst, int row_size);
void test_raw(int *const dst, int *const src, int row_size);
void test_vectorize(int *const dst, int *const src, int row_size);

void
print_time(char *const what, long elapsed) {
  printf("%16s, escaped %8li cpu time, %16lf sec\n",
         what, elapsed, (double)elapsed/CLOCKS_PER_SEC);
}

void
fill(int *const array, int row_size) {
  for (int i = 0; i < row_size; i++) {
    array[i] = i;
  }
}

void
raw(int *const dst, int *const src, int row_size) {
  for (int i = 0; i < row_size; i++) {
    dst[i] = src[i];
  }
}

void
vectorize(int *const dst, int *const src, int row_size) {
  for (int i = 0; i < row_size; i += NM_LOOP_VECTOR_WIDTH) {
    dst[i] = src[i];
    dst[i+1] = src[i+1];
    dst[i+2] = src[i+2];
    dst[i+3] = src[i+3];
  }
}

int
validate(int *const a, int *const b, int row_size) {
  int i = 0;
  for (; i < row_size; i++) {
    if (a[i] != b[i]) {
      goto clean_exit;
    }
  }
 clean_exit:
  return i;
}

void
test_fill(int *const dst, int row_size) {
  clock_t elapsed;
  _time_(fill(dst, row_size), elapsed);
  print_time("fill", elapsed);
}

void
test_raw(int *const dst, int *const src, int row_size) {
  clock_t elapsed;
  _time_(raw(dst, src, row_size), elapsed);
  print_time("raw", elapsed);
}

void
test_vectorize(int *const dst, int *const src, int row_size) {
  clock_t elapsed;
  _time_(vectorize(dst, src, row_size), elapsed);
  print_time("vectorize", elapsed);
}

int
main(void) { 
  int *array = calloc(sizeof(int), ROW_SIZE);
  int *raw = calloc(sizeof(int), ROW_SIZE);
  int *vectorize = calloc(sizeof(int), ROW_SIZE);

  test_fill(array, ROW_SIZE);
  test_vectorize(vectorize, array, ROW_SIZE);
  test_raw(raw, array, ROW_SIZE);
  
  printf("validate(raw, vectorize, %i): %s\n", ROW_SIZE,
         validate(raw, vectorize, ROW_SIZE) ? "false" : "true");

  free(array);
  free(vectorize);

  return 0;
}
