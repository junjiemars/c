#include <_cc_.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BSIZE 128
#define MAX_TOKEN_LEN 32
#define MAX_TOKEN_NUM 32

enum token_t {
	IDENTIFIER, QUALIFIER, TYPE
};

struct token_s {
	char type;
	char string[MAX_TOKEN_LEN];
};

int top = -1;
struct token_s stack[MAX_TOKEN_NUM];
struct token_s token;

#define pop stack[top--]
#define push(s) stack[++top] = s

char inbuf[BSIZE];
char *inptr;

int lookahead(void);
void pushback(void);
enum token_t classify_string(void);
void get_token(void);

int lookahead(void) {
	if ('\0' == *inptr || inptr >= inbuf + BSIZE - 1) {
		return EOF;
	}
	return *inptr++;
}

void pushback(void) {
	if (inbuf < inptr) {
		inptr--;
	}
}

enum token_t 
classify_string(void) {
	char *s = token.string;
	if (0 == strcmp(s, "const")) return QUALIFIER;
	if (0 == strcmp(s, "volatile")) return QUALIFIER;
	if (0 == strcmp(s, "char")) return TYPE;
	if (0 == strcmp(s, "signed")) return TYPE;
	if (0 == strcmp(s, "unsigned")) return TYPE;
	if (0 == strcmp(s, "short")) return TYPE;
	if (0 == strcmp(s, "int")) return TYPE;
	if (0 == strcmp(s, "long")) return TYPE;
	if (0 == strcmp(s, "float")) return TYPE;
	if (0 == strcmp(s, "double")) return TYPE;
	if (0 == strcmp(s, "struct")) return TYPE;
	if (0 == strcmp(s, "union")) return TYPE;
	if (0 == strcmp(s, "enum")) return TYPE;
	return IDENTIFIER;
}

void
get_token(void) {
	char *p = token.string;
	while (isblank(*p = lookahead())) ;
	
	if (isalnum(*p)) {
		while (isalnum(*++p = lookahead())) ;
		pushback();
		*p = '\0';
		token.type = classify_string();
		return;
	}

	if ('*' == *p) {
		strcpy(token.string, "pointer to");
		token.type = '*';
		return;
	}

	token.string[1] = '\0';
	token.type = *p;
	return;
}

void
read_to_first_identifier(void) {
	get_token();
	while (IDENTIFIER != token.type) {
		push(token);
		get_token();
	}
	printf("%s as ", token.string);
	get_token();
}

void
deal_with_arrays(void) {
	while ('[' == token.type) {
		printf("array ");
		get_token();
		if (isdigit(token.string[0])) {
			printf("0..%d ", atoi(token.string)-1);
			get_token();
		}
		get_token();
		printf("of ");
	}
}

void
deal_with_function_args(void) {
	while (')' == token.type) {
		get_token();
	}
	get_token();
	printf("function returning ");
}

void
deal_with_pointers(void) {
	while ('*' == stack[top].type) {
		printf("%s ", pop.string);
	}
}

void
deal_with_declarator(void) {
	switch (token.type) {
	case '[': deal_with_arrays(); break;
	case '(': deal_with_function_args();
	}
	deal_with_pointers();
	while (top >= 0) {
		if ('(' == stack[top].type) {
			pop;
			get_token();
			deal_with_declarator();
		} else {
			printf("%s ", pop.string);
		}
	}
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		strcpy(inbuf, argv[1]);
		inptr = inbuf;
		read_to_first_identifier();
		deal_with_declarator();
		printf("\n");
	}

	return 0;
}
