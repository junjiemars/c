#include "../_lang_.h"

int
main (void)
{
  return 0;
}

void
test_pointer_type (void)
{
  char s[] = "lang/type";
  ptrdiff_t p20 = &s[2] - &s[0];
  ptrdiff_t p02 = &s[0] - &s[2];

  printf ("%20s=%02zu, %20s, %p\n", "sizeof(char*0)", sizeof (&s[0]), s,
          (unsigned long *)&s[0]);
  printf ("%20s=%02zu, %20s, %p\n", "sizeof(char*1)", sizeof (&s[1]), s,
          (unsigned long *)&s[1]);
  printf ("%20s=%02zu, %20s, %p\n", "sizeof(char*2)", sizeof (&s[2]), s,
          (unsigned long *)&s[2]);
  printf ("%20s=%02zu, %020td\n", "sizeof(ptrdiff_t)", sizeof (p20), p20);
  printf ("%20s=%02zu, %020td\n", "sizeof(ptrdiff_t)", sizeof (p02), p02);
}
