#include <_cc_.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>


#define BSIZE  128
#define EOS    '\0'
#define STRMAX 64
#define SYMMAX 32

enum token_e {
	NUM = 256,
	PUL,
	SUB,
	MUL,
	DIV,
	DONE,
};

char inbuf[BSIZE];
char *inptr;

char lexbuf[BSIZE];
char lexemes[STRMAX];
int tokenval;
int lastentry = 0;
int lastchar = -1;


struct entry_s {
	char *lexptr;
	enum token_e token;
} symtable[SYMMAX];

void error(char *, ...);
int lookahead(void);
void pushback(void);
int lexan(void);
int lookup(char *);
int insert(char *, enum token_e);

void error(char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	fprintf(stderr, fmt, args);
	va_end(args);
	exit(1);
}

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

int lexan(void) {
	int c = lookahead();
	while (1) {
		if (isblank(c)) {
			; /* skip */
		} else if (isdigit(c)) {
			tokenval = c - '0';
			c = lookahead();
			while (isdigit(c)) {
				tokenval = tokenval * 10 + c - '0';
				c = lookahead();
			}
			return NUM;
		} else if (ispunct(c)) {
			switch (c) {
			case '+': c = lookahead(); return PUL;
			case '-': c = lookahead(); return SUB;
			case '*': c = lookahead(); return MUL;
			case '/': c = lookahead(); return DIV;
			default:  error("!panic, invalid character: '%s'\n", c);
			};
		}	else if (EOF == c) {
			return DONE;
		}
  }
}

int lookup(char *s) {
	for (int p = lastentry; p > 0; p--) {
		if (0 == strncmp(symtable[p].lexptr, s, STRMAX)) {
			return p;
		}
	}
	return 0;
}

int insert(char *s, enum token_e tok) {
	int len = (int)strlen(s);
	if (lastentry + 1 >= SYMMAX) {
		error("!panic, symbol table full\n");
	}
	if (lastchar + len + 1 >= STRMAX) {
		error("!panic, lexemes array full\n");
	}
	lastentry++;
	symtable[lastentry].token = tok;
	symtable[lastentry].lexptr = &lexemes[lastchar+1];
	lastchar += len+1;
	strcpy(symtable[lastentry].lexptr, s);
	return lastentry;
}

void test_lookahead(char *buf) {
	strncpy(inbuf, buf, BSIZE);
	int c;
	while (EOF != (c = lookahead())) {
		fprintf(stdout, "%c, ", (int)c);
	}
}

void test_pushback(char *buf) {
	strncpy(inbuf, buf, BSIZE);
	int c, p;
	c = lookahead();
	pushback();
	p = lookahead();
	assert(c == p && "test_pushback failed");
}

void test_lexan(char *buf) {
	strncpy(inbuf, buf, BSIZE);
	int tok;
	while (DONE != (tok = lexan())) {
		fprintf(stdout, "%d |", tok);
	}
	fprintf(stdout, "\n");
}


void test_insert(void) {
	if (0 == lookup("123")) {
		insert("123", NUM);
	}
	if (0 == lookup("+")) {
		insert("+", PUL);
	}
	if (0 == lookup("345")) {
		insert("345", NUM);
	}
	assert(1 == lookup("123") && "lookup('123') == 1");
	assert(2 == lookup("+") && "lookup('+') == 2");
	assert(3 == lookup("345") && "lookup('345') == 3");
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	if (argc > 1) {
		inptr = inbuf;
		test_lookahead(argv[1]);
		inptr = inbuf;
		test_pushback(argv[1]);
		inptr = inbuf;
		test_lexan(argv[1]);
		test_insert();
	}
	return 0;
}
