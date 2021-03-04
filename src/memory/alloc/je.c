#include <_memory_.h>
#include <jemalloc/jemalloc.h>

void test_malloc(void);
void test_calloc(void);
void test_posix_memalign(void);
void test_aligned_alloc(void);
void test_realloc(void);
void test_free(void);

void
test_malloc(void)
{
}

void
test_calloc(void)
{
}

void
test_posix_memalign(void)
{
}

void
test_aligned_alloc(void)
{
}

void
test_realloc(void)
{
}

void
test_free(void)
{
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);
  
  test_malloc();
  test_calloc();
  test_posix_memalign();
  test_aligned_alloc();
  test_realloc();
  test_free();

  return 0;
}
