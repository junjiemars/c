#include "../_lang_.h"
#include <assert.h>
#include <stdlib.h>

#if defined(GCC) || defined(CLANG)
union __attribute__ ((packed)) size_u
{
  struct
  {
    short high;
    short low;
  } split;
  int whole;
};
#elif defined(MSVC)
#pragma pack(push, 1)
union size_u
{
  struct
  {
    short high;
    short low;
  } split;
  int whole;
};
#pragma pack(pop)
#endif

void test_size_u (void);
void test_cast (void);

void
test_size_u (void)
{
  union size_u u1 = { .whole = 0 };
  assert (sizeof (u1) == sizeof (u1.whole));

  u1.split.high = 0x1122;
  u1.split.low = 0x3344;

#if NM_CPU_LITTLE_ENDIAN
  assert (u1.whole == 0x33441122);
#else
  assert (u1.whole == 0x11223344);
#endif
}

void
test_cast (void)
{
  union size_u *u1 = malloc (sizeof (*u1));
  u1->whole = 0x11223344;

  union size_u *u2 = malloc (sizeof (*u2));
  u2->whole = *(int *)u1;
  assert (u2->whole == u1->whole);

  u2->whole++;
  union size_u *u3;
  u3 = (union size_u *)&u2->whole;
  assert (u3->whole == u2->whole);

  free (u1);
  free (u2);
}

int
main (void)
{

  test_size_u ();
  test_cast ();

  return 0;
}
