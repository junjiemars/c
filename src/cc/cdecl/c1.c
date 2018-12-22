#include <_parser_.h>
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
	printf("type=%c, string=%s\n", token->type, token->string);
	return token->type;
}

void get_token(char *input, struct token_s *token) {
	char c;
	char *s = token->string;

	while ((c = *input++)) {
		if (isalpha(c)) {
			*s++ = c;
		} else if ('(' == c) {
			*s++ = c;
		} else if (')' == c) {
			*s++ = c;
			classify_string(token);
		} else if (' ' == c) {
			classify_string(token);
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
