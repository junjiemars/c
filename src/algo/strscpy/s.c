#include <_algo_.h>

#if (GCC)
#  include <sys/types.h>
#elif (MSVC)
#  include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif


/* 
   https://github.com/torvalds/uemacs/commit/9be85a9b60677acc8f8c6da048a0c08e67e172f8 
   Safe zeroing, no complaining about overlap
*/

char *
strscpy(char *dst, const char *src, size_t size)
{
	if (!size) return 0;
	char *p = dst;
	while (--size)
    {
      char c = *src++;
      if (!c) break;
      *dst++ = c;
    }
	*dst = 0;
	return p;
}

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);
	char s[] = "abc";
	char *s1 = strscpy(s, s, sizeof(s));
	printf("%s\n", s1);
	return 0;
}
