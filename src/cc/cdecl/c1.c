#include <_cc_.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>


#define MAX_TOKEN_LEN 32
#define MAX_TOKEN_NUM 32

struct token_s {
	char type;
	char string[MAX_TOKEN_LEN];
};

struct token_s stack[MAX_TOKEN_NUM];
struct token_s token;
int token_idx = 0;

void get_token(char*, struct token_s*);
char classify_string(struct token_s *);


char classify_string(struct token_s *tok) {
	if (strncmp("char", tok->string, MAX_TOKEN_LEN)
			|| strncmp("intp", tok->string, MAX_TOKEN_LEN)) {
		tok->type = 't';
	} else if (strncmp("const", tok->string, MAX_TOKEN_LEN)
						 || strncmp("volatile", tok->string, MAX_TOKEN_LEN)) {
		tok->type = 'q';
	} else {
		tok->type = 'i';
	}
	printf("type=%c, string=%s\n", tok->type, tok->string);
	return tok->type;
}

void get_token(char *input, struct token_s *tok) {
	char c;
	char *s = tok->string;

	while (EOF != (c = *input++)) {
		if (isalpha(c)) {
			*s++ = c;
		} else if ('(' == c) {
			*s++ = c;
		} else if (')' == c) {
			*s++ = c;
			classify_string(tok);
		} else if (' ' == c) {
			classify_string(tok);
		}
	}
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		get_token(argv[1], &token);
	}

	return 0;
}
