#include <_str_.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void 
str_len() {
	char *s[] = { "abc123", "abc123中文", 0 };
	for (char **p = s; *p; p++) {
		printf("strlen(%s) = %lu\n", *p, strlen(*p));
	}

	printf("strnlen(%s, %i) = %lu\n", *s, 4, strnlen(*s, 4));
}

void str_copy() {
	char *s = "abc123";
	char *d;
	size_t maxlen = 4;

	d = malloc(strlen(s)+1); 
	printf("strcpy(%p, %s) = %s, %lu chars\n", d, s, strcpy(d, s), strlen(d));
	free(d);

	d = calloc(0, maxlen+1);
	printf("strncpy(%p, %s, %lu) = %s, %lu chars\n", 
		d, s, maxlen, strncpy(d, s, maxlen), strnlen(d, maxlen));
	free(d);

	d = calloc(0, strlen(s)+1);
	printf("stpcpy(%p, %s) = %s, %lu chars, %s\n", d, s, stpcpy(d, s), strlen(d), d);
	free(d);

	d = calloc(0, maxlen+1);
	printf("stpncpy(%p, %s, %lu) = %s, %lu chars, %s\n", 
		d, s, maxlen, stpncpy(d, s, maxlen), strnlen(d, maxlen), d);
	free(d);
}

void str_cat() {
	char d[16] = "abc123";
	char s[16] = "def";
	printf("d = %s strlen(d) = %lu sizeof(d) = %lu\n",
				 d, strlen(d), sizeof(d));
	printf("s = %s strlen(s) = %lu sizeof(s) = %lu\n",
				 s, strlen(s), sizeof(s));

	if (strlen(d) + 1 <= sizeof(s) + strlen(s)) {
			char *n = strncat(d, s, sizeof(s) - strlen(s) - 1);
			printf("n = %s strlen(n)=%lu sizeof(n) = %lu\n",
						 n, strlen(n), sizeof(d));
	}
}

void str_chr() {
	 const char *s = "abc123";
	 printf("strchr(s, %c) = %s\n", 'b', strchr(s, 'b'));
	 printf("strchr(s, %c) = %s\n", '\0', strchr(s, '\0'));
}


void str_cmp() {
	const char *l = "abc123";
	const char *r = "abc1234";
	const char *r1 = "abc122";
	printf("strcmp(%s, %s) = %i\n", l, r, strcmp(l, r));
	printf("strcmp(%s, %s) = %i\n", l, r1, strcmp(l, r1));
}

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\nSTRING LENGTH\n");
	printf("----------\n");
	str_len();

	printf("\nSTRING COPY\n");
	printf("----------\n");
	str_copy();

	printf("\nSTRING LENGTH\n");
	printf("----------\n");
	str_cat();

	printf("\nSTRING LENGTH\n");
	printf("----------\n");
	str_chr();

	printf("\nSTRING LENGTH\n");
	printf("----------\n");
	str_cmp();
}
