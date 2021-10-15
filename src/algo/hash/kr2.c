#include <_algo_.h>
#include <stdio.h>
#include "_hash_.h"


unsigned long
hash(const char *str)
{
	unsigned long h;
	for (h = 0; *str; str++)
    {
      h = *str + 31 * h;
    }
	return h % 1024;
}

int
main(int argc, char **argv)
{
  const char     *ss;
  unsigned long   h;

	if (argc > 1)
    {
      ss = argv[1];
      h =  hash(ss);
      print_hash("K&R hash 2", ss, h);
    }
	return 0;
}
