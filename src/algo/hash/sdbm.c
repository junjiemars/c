#include <_algo_.h>
#include <stdio.h>
#include "_hash_.h"


unsigned long
hash(const char *str)
{
	unsigned long h = 0;
	int c;
	while (0 != (c = *str++))
    {
      h = c + (h << 6) + (h << 16) - h;
    }
	return h;
}

int
main(int argc, char **argv)
{
  const char     *ss;
  unsigned long   h;

	if (argc > 1)
    {
      ss = argv[1];
      h = hash(ss);
      print_hash("sdbm hash", ss, h);
    }

	return 0;
}
