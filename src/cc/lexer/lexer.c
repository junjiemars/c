#include <_cc_.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct entry_s { /* form of symbol table entry */
	char *lexptr;
	int token;
};

#define DONE -1
#define NONE -1

#define BSIZE 128
#define STRMAX 64
#define SYMMAX 64

#define NUM 256
#define PUL 257
#define SUB 258
#define MUL 259
#define DIV 260


char lexbuf[BSIZE];
char lexemes[STRMAX];
char *lexptr;
int tokenval;
struct entry_s symtable[SYMMAX]; /* symbol table */
int lastchar = -1; /* last used position in lexemes */
int lastentry = 0; /* last used position in symtable, start from 1 */

void error(int, char*);
int lookahead(void);
void pushback(void);
int lexan(void);
int lookup(char*);
int insert(char*, int);

/* generate all error message */
void error(int at, char *m) {
	fprintf(stderr, "at %d: %s\n", at, m);
	exit(1);
}

int lookahead(void) {
	if ('\0' == *lexptr || lexptr >= lexbuf + BSIZE - 1) {
		return EOF;
	}
	return *lexptr++;
}

void pushback(void) {
	if (lexbuf < lexptr) {
		lexptr--;
	}
}

int lexan(void) {
	int c = lookahead();
	while (1) {
		if (isspace(c)) {
			; /* skip */
		} else if (isdigit(c)) {
			tokenval = c - '0';
			c = lookahead();
			while (isdigit(c)) {
				tokenval = tokenval * 10 + c - '0';
				c = lookahead();
			}
			return NUM;
		} else if (EOF == c) {
			return DONE;
		}
	}
}

/* return position of entry for s */
int lookup(char *s) {
	int p;
	for (p = lastentry; p > 0; p--) {
		if (0 == strncmp(symtable[p].lexptr, s, STRMAX)) {
			return p;
		}
	}
	return p;
}

/* return position of entry for s */
int insert(char *s, int tok) {
	int len = (int)strnlen(s, STRMAX);
	if (SYMMAX <= lastentry + 1) {
		error(1, "symbol table full");
	}
	if (STRMAX <= lastchar + len + 1) {
		error(1, "lexemes array full");
	}
	lastentry++;
	symtable[lastentry].token = tok;
	symtable[lastentry].lexptr = &lexemes[lastchar + 1];
	lastchar += len + 1;
	return lastentry;
}


void test_error(void) {
	error(1, "Compilers: Principles, Techniques, and Tools");
}

void test_lookahead(char *buf) {
	strncpy(lexbuf, buf, BSIZE);
	int c;
	while (EOF != (c = lookahead())) {
		fprintf(stdout, "%c |", (int)c);
	}
}

void test_pushback(char *buf) {
	strncpy(lexbuf, buf, BSIZE);
	int c, p;
	c = lookahead();
	pushback();
	p = lookahead();
	assert(c == p && "test_pushback failed");
}

void test_lexan(char *buf) {
	strncpy(lexbuf, buf, BSIZE);
	int tok;
	while (DONE != (tok = lexan())) {
		fprintf(stdout, "%d |", tok);
	}
}

void test_lookup(void) {
	memset(symtable, 0, sizeof(symtable));

	assert(0 == lookup((char*)0) && "lookup(nul) = 0");
	assert(0 == lookup("int") && "lookup('int') = 0");

	lastentry++;
	symtable[lastentry].lexptr = "1234";
	symtable[lastentry].token = NUM;
	assert(1 == lookup("1234") && "lookup('1234') = 1");

	lastentry++;
	symtable[lastentry].lexptr = "+";
	symtable[lastentry].token = PUL;
	assert(2 == lookup("+") && "lookup('+') = 2");

	assert(1 == lookup("1234") && "lookup('1234') = 1");
}

void test_insert(void) {
	lastentry = 0;
	memset(symtable, 0, sizeof(symtable));
	int p;
	
	strncpy(lexemes, "1234", STRMAX);
	p = insert(lexemes, NUM);
	assert(1 == p && 1 == lastentry && "insert('1234', NUM) = 1");

	strncpy(lexemes, "+", STRMAX);
	p = insert(lexemes, PUL);
	assert(2 == p && 2 == lastentry && "insert('+', PUL) = 2");
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

/* 	test_error(); */
	/* test_lookup(); */
	/* test_insert(); */
	if (argc > 1) {
		/* lexptr = lexbuf; */
		/* test_lookahead(argv[1]); */
		/* lexptr = lexbuf; */
		/* test_pushback(argv[1]); */
		lexptr = lexbuf;
		test_lexan(argv[1]);
	}
	return 0;
}
