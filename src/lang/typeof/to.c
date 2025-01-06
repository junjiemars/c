#include "../_lang_.h"

#if (NM_HAVE_TYPEOF)
#define swap(a, b)                                                            \
  do                                                                          \
    {                                                                         \
      typeof (a) _swap_1_ = a;                                                \
      a = b;                                                                  \
      b = _swap_1_;                                                           \
    }                                                                         \
  while (0)
#else
#include <string.h>
#define swap(a, b, w)                                                         \
  do                                                                          \
    {                                                                         \
      unsigned char _swap_2_[w];                                              \
      memcpy (_swap_2_, a, w);                                                \
      memmove (a, b, w);                                                      \
      memcpy (b, _swap_2_, w);                                                \
    }                                                                         \
  while (0)
#endif

void
test_swap (void)
{
  int i1 = 0x1122, i2 = 0x3344;
  printf ("before swap: i1 = 0x%x, i2 = 0x%x\n", i1, i2);
#if NM_HAVE_TYPEOF
  swap (i1, i2);
#else
  swap (&i1, &i2, sizeof (i1));
#endif
  printf ("after swap:  i1 = 0x%x, i2 = 0x%x\n", i1, i2);

  /* char *s1 = "abc", *s2 = "123"; */
  /* printf("before swap: s1 = %s, s2 = %s\n", s1, s2); */
  /* #if NM_HAVE_TYPEOF */
  /* 	swap(s1, s2); */
  /* #else */
  /*   swap(s1, s2, sizeof(char*)); */
  /* #endif */
  /* 	printf("after swap:  s1 = %s, s2 = %s\n", s1, s2); */
}

int
main (void)
{

  test_swap ();
  return 0;
}
