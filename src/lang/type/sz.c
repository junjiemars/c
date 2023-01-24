#include "_lang_.h"


int
main(void)
{
  printf("char\n------------\n");
  printf("sizeof('a')  = %zuB\n", sizeof('a'));
  printf("sizeof(L'a') = %zuB\n", sizeof(L'a'));
  printf("sizeof(u'a') = %zuB\n", sizeof(u'a'));
  printf("sizeof(U'a') = %zuB\n", sizeof(U'a'));

  return 0;
}
