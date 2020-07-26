#include "_lang_.h"
#include <stdio.h>

#if defined(GCC) || defined(CLANG)
union __attribute__((packed)) size_u {
  struct {
    short high;
    short low;
  } split;
  int whole;
};
#elif defined(MSVC)
#pragma packed(push, 1)
union size_u {
  struct {
    short high;
    short low;
  } split;
  int whole;
};
#pragma packed(pop)
#endif

void test_size_u(void);

void
test_size_u(void) {
  union size_u u1 = { .whole=0 };
  printf("sizeof(u1) = %4zu\n", sizeof(u1));

  u1.split.high = 0x1122;
  u1.split.low = 0x3344;
  printf("u1.split.high = 0x%x\n", u1.split.high);
  printf("u1.split.low  = 0x%x\n", u1.split.low);
  printf("u1.whole      = 0x%x\n", u1.whole);
}

int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);
  
  test_size_u();

  return 0;
}
