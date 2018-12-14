#include <_memory_.h>
#include <stdio.h>

void
send(char *to, char *from, int count) {
	int n = (count + 7) / 8;  /* count assumed > 0 */
	switch (count % 8) {
	case 0:    do { *to++ = *from++;
	case 7:         *to++ = *from++;
	case 6:         *to++ = *from++;
	case 5:         *to++ = *from++;
	case 4:         *to++ = *from++;
	case 3:         *to++ = *from++;
	case 2:         *to++ = *from++;
	case 1:         *to++ = *from++;
		         } while (--n > 0);
	}
}

int
main(int argc, char **argv[]) {
	_unused_(argc);
	_unused_(argv);

	char *from = "abcdefghijklmnopqrstuvwxyz";
	char to[32] = {0};

	send(to, from, argc);

	for (char *p=to; *p != 0; p++) {
		printf("%c, ", *p);
	}
	fflush(stdout);
	
	return 0;
}
