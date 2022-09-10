#include <_mach_.h>

struct layout_s
{
  char   c;
  short  s;
  int    i;
};

static void test_struct_in_stack(void);

int
main(void)
{
  return 0;
}

static test_struct_in_stack(void)
{
  struct layout_s  s  =  {'A', 0x1122, 0x11223344};

  assert(s.c == 'A' && s.s == 0x1122 && s.i == 0x11223344);
}
