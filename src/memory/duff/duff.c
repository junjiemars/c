#include <_memory_.h>
#include <stdio.h>
#include <string.h>

void
raw_send(char *to, char *from, int count) {
	do {
		*to++ = *from++;
	} while (--count > 0); /* count > 0 assumed */
}

void
send(char *to, char *from, int count) {
	int n = (count + 7) / 8;  /* count > 0 assumed */
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

void
send2(char *to, char *from, int count) {
	int n = (count + 7) / 8; /* count > 0 assumed */
	switch (count % 8) {
	case 0: *to++ = *from++; 
	case 7: *to++ = *from++;
	case 6: *to++ = *from++;
	case 5: *to++ = *from++;
	case 4: *to++ = *from++;
	case 3: *to++ = *from++;
	case 2: *to++ = *from++;
	case 1: *to++ = *from++;
	} while (--n > 0) {
      *to++ = *from++; 
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
      *to++ = *from++;
	}
}

void show(char *p) {
	while (*p != 0) {
		printf("%c, ", *p++);
	}
	printf("\n");
}

int
main(int argc, char **argv[]) {
	_unused_(argc);
	_unused_(argv);

	char *from = "abcdefghijklmnopqrstuvwxyz";
	char to[32] = {0};

	raw_send(to, from, argc);
	show(to);
	fflush(stdout);
	memset(to, 0, sizeof(to)/sizeof(to[0]));
	
	send(to, from, argc);
	show(to);
	fflush(stdout);
	memset(to, 0, sizeof(to)/sizeof(to[0]));

	send2(to, from, argc);
	show(to);
	fflush(stdout);
	memset(to, 0, sizeof(to)/sizeof(to[0]));

	memcpy(to, from, argc);
	show(to);
	fflush(stdout);
	
	return 0;
}
