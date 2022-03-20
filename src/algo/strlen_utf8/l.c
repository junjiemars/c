#include <_algo_.h>

static size_t strlen_utf8(const char*);

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

	char *s = "a中文bc12def";
	size_t n = strlen_utf8(s);
	printf("strlen_utf8(%s) = %zu\n", s, n);

	return 0;
}


size_t
strlen_utf8(const char *s)
{
	size_t n = 0, i = 0;
	while (s[i]) {
		if ((0xc0 & s[i]) != 0x80)
      {
        n++;
      }
		i++;
	}
	return n;
}
