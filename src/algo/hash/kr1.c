#include "_algo_.h"
#include <stdio.h>
#include "_hash_.h"

unsigned long
hash (const char *str)
{
	int            c;
	unsigned long  h  =  0;
  
	while (0 != (c = *str++))
    {
      h += c;
    }
	return h;
}

int
main(int argc, char **argv)
{
  const char     *ss;
  unsigned long   h;

	_unused_(argc);

	if (argc > 1)
    {
      ss = argv[1];
      h = hash(ss);
      print_hash("K&R hash 1", ss, h);
    }
	
	return 0;
}
