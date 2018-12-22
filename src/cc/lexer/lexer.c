#include <_cc_.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
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
int lastentry = 0; /* last used position in symtable */

int lookup(char*);

/* return position of entry for s */
int lookup(char *s) {
	for (int p = lastentry; p > 0; p--) {
		if (0 == strncmp(symtable[p].lexptr, s, STRMAX)) {
			return p;
		}
	}
	return 0;
}
	
void test_lookup(void) {
	assert(0 == lookup((char*)0) && "lookup(nul) = 0");
	assert(0 == lookup("int") && "lookup('int') = 0");

	symtable[lastentry].lexptr = "1234";
	symtable[lastentry].token = NUM;
	lastentry++;
	symtable[lastentry].lexptr = "+";
	symtable[lastentry].token = ADD;

	assert(0 == lookup("1234") && "lookup('1234') = 0");
	assert(1 == lookup("+") && "lookup('+') = 1");
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	test_lookup();
	return 0;
}
