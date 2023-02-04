#include "_lang_.h"

static void test_char();


int
main(void)
{
  test_char();

  return 0;
}

void
test_char()
{
  printf("char\n------------\n");
  printf("sizeof('a')  = %zuB\n", sizeof('a'));
  printf("sizeof(L'a') = %zuB\n", sizeof(L'a'));
  printf("sizeof(u'a') = %zuB\n", sizeof(u'a'));
  printf("sizeof(U'a') = %zuB\n", sizeof(U'a'));
}
