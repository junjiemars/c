#include "../_lang_.h"

static void test_char ();
static void test_int ();

int
main (void)
{
  test_char ();
  test_int ();

  return 0;
}

void
test_char ()
{
  printf ("char\n------------\n");
  printf ("sizeof('a')  = %zuB\n", sizeof ('a'));
  printf ("sizeof(L'a') = %zuB\n", sizeof (L'a'));
  printf ("sizeof(u'a') = %zuB\n", sizeof (u'a'));
  printf ("sizeof(U'a') = %zuB\n", sizeof (U'a'));
}

void
test_int ()
{
  printf ("int\n------------\n");
  printf ("sizeof(short int)  = %zuB\n", sizeof (short int));
  printf ("sizeof(int) = %zuB\n", sizeof (int));
  printf ("sizeof(long int) = %zuB\n", sizeof (long int));
  printf ("sizeof(long long int) = %zuB\n", sizeof (long long int));
}
