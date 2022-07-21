#include <_lang_.h>

static int n;
static volatile int n1;

void
bar(void)
{
	/* with clang -O2 optimized will keep function skeleton, just
		 like:
		 void bar(void)
{}
		 because n has ever changed
 */
	n = 0;
	int i = 0;
	while (n != 255)
{
		if (++i > 3)
{
			break;
		}
	}
}

void
bar1(void)
{
	n1 = 0;
	int i = 0;
	while (n1 != 255)
{
		if (++i > 3)
{
			break;
		}
	}
}

int
incr(void)
{
	n1 += 0xff;
	return n1;
}

int
main(void)
{

	bar();
	bar1();
	incr();

	return 0;
}
