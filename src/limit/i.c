#include "_limit_.h"

int
main(void)
{
  printf(FMT_S_L32(FMT_I_RD), _str_(CHAR_BIT), CHAR_BIT);
  printf(FMT_S_L32(FMT_I_RD), _str_(CHAR_MAX), CHAR_MAX);
  printf(FMT_S_L32(FMT_I_RD), _str_(CHAR_MIN), CHAR_MIN);
  printf(FMT_S_L32(FMT_I_RD), _str_(SCHAR_MAX), SCHAR_MAX);
  printf(FMT_S_L32(FMT_I_RD), _str_(SCHAR_MIN), SCHAR_MIN);
  printf(FMT_S_L32(FMT_I_RD), _str_(INT_MAX), INT_MAX);
  printf(FMT_S_L32(FMT_I_RD), _str_(INT_MIN), INT_MIN);
  printf(FMT_S_L32(FMT_I_RU), _str_(UINT_MAX), UINT_MAX);
  printf(FMT_S_L32(FMT_I_RD), _str_(SHRT_MAX), SHRT_MAX);
  printf(FMT_S_L32(FMT_I_RD), _str_(SHRT_MIN), SHRT_MIN);
  printf(FMT_S_L32(FMT_I_RD), _str_(USHRT_MAX), USHRT_MAX);
  printf(FMT_S_L32(FMT_I_RLD), _str_(LONG_MAX), LONG_MAX);
  printf(FMT_S_L32(FMT_I_RLD), _str_(LONG_MIN), LONG_MIN);
  printf(FMT_S_L32(FMT_I_RLU), _str_(ULONG_MAX), ULONG_MAX);
  printf(FMT_S_L32(FMT_I_RLLD), _str_(LLONG_MAX), LLONG_MAX);
  printf(FMT_S_L32(FMT_I_RLLD), _str_(LLONG_MIN), LLONG_MIN);
  printf(FMT_S_L32(FMT_I_RLLU), _str_(ULLONG_MAX), ULLONG_MAX);
  printf(FMT_S_L32(FMT_I_RD), _str_(MB_LEN_MAX), MB_LEN_MAX);

  return 0;
}
