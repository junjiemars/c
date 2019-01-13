#include <_algo_.h>
#include <string.h>
#include <stdio.h>


void
reverse_string(char *s) {
	for (int i=0, j=strlen(s)-1; i<j; i++, j--) {
		int t = s[i];
		s[i] = s[j];
		s[j] = t;
	}
}


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	char s[256];
	strcpy(s, argv[0]);
	reverse_string(s);
	printf("reversed: %s", s);

	return 0;
}
