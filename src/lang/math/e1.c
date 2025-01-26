#include "../_lang_.h"
#include <float.h>
#include <math.h>

#ifdef NM_HAVE_FENV_H
#include <fenv.h>
/* #if (MSVC) */
/* #pragma stdc fenv_access(on) */
/* #else */
/* #pragma STDC FENV_ACCESS ON */
/* #endif */
#endif

int
main (void)
{
#ifdef FLT_ROUNDS
  printf ("%s(%d)\n", _str_ (FLT_ROUNDS), FLT_ROUNDS);
#endif /* FLT_ROUNDS */

#ifdef FLT_RADIX
  printf ("%s(%d)\n", _str_ (FLT_RADIX), FLT_RADIX);
#endif /* FLT_RADIX */

#ifdef FLT_MIN
  printf ("%s(%g)\n", _str_ (FLT_MIN), FLT_MIN);
#endif /* FLT_MIN */

#ifdef FLT_MAX
  printf ("%s(%g)\n", _str_ (FLT_MAX), FLT_MAX);
#endif /* FLT_MAX */

#ifdef NM_HAVE_FENV_H
  int round;

  round = fegetround ();
  switch (round)
    {
    case FE_TONEAREST:
      printf ("default rounding direction: %s(%d)\n", _str_ (FE_TONEAREST),
              round);
      break;
    case FE_TOWARDZERO:
      printf ("default rounding direction: %s(%d)\n", _str_ (FE_TOWARDZERO),
              round);
      break;
    case FE_DOWNWARD:
      printf ("default rounding direction: %s(%d)\n", _str_ (FE_DOWNWARD),
              round);
      break;
    case FE_UPWARD:
      printf ("default rounding direction: %s(%d)\n", _str_ (FE_UPWARD),
              round);
      break;
#ifdef FE_TONEAREST_MAX_MAGNITUDE
    case FE_TONEAREST_MAX_MAGNITUDE:
      printf ("default rounding direction: %s(%d)\n",
              _str_ (FE_TONEAREST_MAX_MAGNITUDE), round);
      break;
#endif /* FE_TONEAREST_MAX_MAGNITUDE */
#ifdef FE_DYNAMIC
    case FE_DYNAMIC:
      printf ("default rounding direction: %s(%d)\n", _str_ (FE_DYNAMIC),
              round);
      break;
#endif /* FE_DYNAMIC */
    default:
      printf ("default rounding direction: %s(%d)\n", "unkown", round);
      break;
    }
#endif
  return 0;
}
