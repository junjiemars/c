#include <_algo_.h>
#include <string.h>
#include <stdio.h>


#if MSVC
# pragma warning(disable: 4996)
#endif

void
reverse_string(char *s) {
	for (size_t i=0, j=strlen(s)-1; i<j; i++, j--) {
		int t = s[i];
		s[i] = s[j];
		s[j] = (char)t;
	}
}


int
main(__attribute__((unused)) int argc, char **argv)
{
	char  s[256];

	strcpy(s, argv[0]);
	reverse_string(s);
	printf("reversed: %s", s);

	return 0;
}
