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
struct token_s token;

void get_token(const char *);
char classify_string(struct token_s *);

char classify_string(struct token_s *token) {
	if (strncmp("char", token->string, MAX_TOKEN_LEN)
			|| strncmp("intp", token->string, MAX_TOKEN_LEN)) {
		token->type = 't';
	} else if (strncmp("const", token->string, MAX_TOKEN_LEN)
						 || strncmp("volatile", token->string, MAX_TOKEN_LEN)) {
		token->type = 'q';
	} else {
		token->type = 'i';
	}
}

void get_token(const char *input, int *idx) {
	if (0 == *pointer) {
		return;
	}
	
	const char *p;
	struct token t = stack[idx];

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
