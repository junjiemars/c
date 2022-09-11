#include <_algo_.h>

/*
 * Loop Tiling:
 *
 *
 * Refs:
 *
 */


#define ROW_SIZE (NM_CPU_CACHE_LINE * 16)
#define COL_SIZE (NM_CPU_CACHE_LINE * 16)

#define N  NM_CPU_CACHE_LINE
#define X  0x11


static void tile(char *const, int, int);
static void print_time(char *const, long);
static int validate(const char*, const char*);
static void test_raw(char *const);
static void test_tile(char *const);


int
main(void)
{
  char          *raw, *tile, *tile1;
  const size_t   size  =  sizeof(char) * ROW_SIZE * COL_SIZE;

  raw = calloc(1, size);
  tile = calloc(1, size);
  tile1 = calloc(1, size);

  test_raw(raw);
  test_tile(tile);
  test_tile(tile1);

  printf("validate(raw, tile): %s\n",
         validate(raw, tile) ? "false" : "true");

  free(raw);
  free(tile);
  free(tile1);

  return 0;
}


void
tile(char *const table, int row_size, int col_size)
{
  for (int i = 0; i < row_size; i += N)
    {
      for (int j = 0; j < col_size; j += N)
        {
          for (int k = j; k < _min_(j+N, col_size); k++)
            {
              for (int l = i; l < _min_(i+N, row_size); l++)
                {
                  table[l*k+k] = X;
                }
            }
        }
    }
}


void
print_time(char *const what, long elapsed)
{
  printf("%8s, escaped %8li cpu time, %16lf sec\n",
         what, elapsed, (double)elapsed/CLOCKS_PER_SEC);
}

void
raw(char *const table, int row_size, int col_size)
{
  for (int i = 0; i < row_size; i++)
    {
      for (int j = 0; j < col_size; j++)
        {
          table[i*j+j] = X;
        }
    }
}


int
validate(const char *a, const char *b)
{
  for (int i = 0; i < ROW_SIZE; i++)
    {
      for (int j = 0; j < COL_SIZE; j++)
        {
          if (a[i*j+j] != b[i*j+j])
            {
              return 1;
            }
        }
    }
  return 0;
}

void
test_raw(char *const table)
{
  clock_t elapsed;
  _time_(raw(table, ROW_SIZE, COL_SIZE), elapsed);
  print_time("raw", elapsed);
}

void
test_tile(char *const table)
{
  clock_t elapsed;
  _time_(tile(table, ROW_SIZE, COL_SIZE), elapsed);
  print_time("tile", elapsed);
}
