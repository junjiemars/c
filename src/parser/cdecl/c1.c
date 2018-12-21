#include <_parser_.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_TOKEN_LEN 32
#define MAX_TOKEN_NUM 32

struct token_s {
	char type;
	char string[MAX_TOKEN_LEN];
};

struct token_s stack[MAX_TOKEN_NUM];

void get_token(const char *);

void get_token(const char *input, int *idx) {
	if (0 == *pointer) {
		return;
	}
	
	const char *p;
	
	while (0 != (p = pointer++)) {
		if (isalpha(*p)) {
		}
	}
	return;
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("a=%i, A=%i\n", 'a', 'A');
	return 0;
}
