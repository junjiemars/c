#include <_lang_.h>


#define sa_cat_(a, b) a##b
#define sa_cat(a, b) sa_cat_(a, b)

int
main(void)
{
  printf("sa_cat(%s, %s) = %s\n", _str_(first), _str_(second),
         sa_cat(first, second));
	return 0;
}
