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

#define STRMAX 64
#define SYMMAX 64

#define NUM 256
#define ADD 257
#define SUB 258
#define MUL 259
#define DIV 260

struct entry_s symtable[SYMMAX]; /* symbol table */
char lexemes[STRMAX]; 
int lastchar = -1; /* last used position in lexemes */
int lastentry = 0; /* last used position in symtable, start from 1 */

void error(int, char*);
int lookup(char*);
int insert(char*, int);

/* generate all error message */
void error(int at, char *m) {
	fprintf(stderr, "at %d: %s\n", at, m);
	exit(1);
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
	int len = strnlen(s, STRMAX);
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
	symtable[lastentry].token = ADD;
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
	p = insert(lexemes, ADD);
	assert(2 == p && 2 == lastentry && "insert('+', ADD) = 2");
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

/* 	test_error(); */
	test_lookup();
	test_insert();
	return 0;
}
