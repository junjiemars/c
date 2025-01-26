#include "../_algo_.h"
#include <limits.h>

#define LIMIT_U_MAX(t) ((t)~0)
#define LIMIT_U_MIN(t) (0)

#define LIMIT_S_MAX(t) (((t)1 << (sizeof (t) * CHAR_BIT - 1)) - 1)
#define LIMIT_S_MIN(t) ((t)(-(LIMIT_S_MAX (t)) - 1))

static int char_bit (void);

int
main (void)
{
  assert (CHAR_BIT == char_bit ());

  if (!_isut_ (char))
    {
      assert (CHAR_MIN == LIMIT_S_MIN (char));
      assert (CHAR_MAX == LIMIT_S_MAX (char));
    }
  assert (UCHAR_MAX == LIMIT_U_MAX (unsigned char));

  assert (SHRT_MAX == LIMIT_S_MAX (short));
  assert (SHRT_MIN == LIMIT_S_MIN (short));
  assert (USHRT_MAX == LIMIT_U_MAX (unsigned short));

  assert (INT_MIN == LIMIT_S_MIN (int));
  assert (INT_MAX == LIMIT_S_MAX (int));
  assert (UINT_MAX == LIMIT_U_MAX (unsigned int));

  assert (LONG_MIN == LIMIT_S_MIN (long));
  assert (LONG_MAX == LIMIT_S_MAX (long));
  assert (ULONG_MAX == LIMIT_U_MAX (unsigned long));

  assert (LLONG_MIN == LIMIT_S_MIN (long long));
  assert (LLONG_MAX == LIMIT_S_MAX (long long));
  assert (ULLONG_MAX == LIMIT_U_MAX (unsigned long long));

  return 0;
}

int
char_bit (void)
{
  int n = 1;
  for (char c = 1; c > 0; c <<= 1)
    {
      n++;
    }
  return n;
}
