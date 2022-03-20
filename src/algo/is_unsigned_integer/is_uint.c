#include <_algo_.h>

#define IS_UNSIGNED_INTEGER(x) ((x) > 0 && ~(x) > 0)

#if (GCC)
#  pragma GCC diagnostic ignored "-Wsign-compare"
#endif

int main(void)
{
	char c1 = 0x11;
	unsigned c2 = 0x22;

	printf("c1 is unsigned: %d\n",  IS_UNSIGNED_INTEGER(c1));
	printf("c2 is unsigned: %d\n",  IS_UNSIGNED_INTEGER(c2));

	return 0;
}
