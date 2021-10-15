#include <_algo_.h>
#include <stdio.h>
#include "_hash_.h"


/* Dan Bernstein */
unsigned long
hash(const char *str)
{
	unsigned long h = 5381;
	int c;
	while (0 != (c = *str++))
    {
      h = ((h << 5) + h) + c;
    }
	return h;
}

int
main(int argc, char **argv)
{
  const char *ss;
  unsigned long h;

	if (argc > 1)
    {
      ss = argv[1];
      h = hash(ss);
      print_hash("djb2 hash", ss, h);
    }
	return 0;
}
