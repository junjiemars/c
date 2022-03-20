#include "_hash_.h"

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
