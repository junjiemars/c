#include "_hash_.h"


int
main(int argc, char **argv)
{
  const char     *ss;
  unsigned long   h;

	if (argc > 1)
    {
      ss = argv[1];
      h = hash(argv[1]);
      print_hash("Jenkins hash", ss, h);
    }
	return 0;
}


unsigned long
hash(const char *str)
{
	int            c;
	unsigned long  h  =  0;

	while (0 != (c = *str++))
    {
      h += c;
      h += h << 10;
      h ^= h >> 6;
    }
	h += h << 3;
	h ^= h >> 11;
	h += h << 15;
	return h;
}
