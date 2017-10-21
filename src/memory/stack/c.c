#include <_memory_.h>
#include "stack.h"
#include <stdio.h>

void 
int_stack() {
	printf("\nINT STACK\n");
	printf("----------\n");
	printf("pushed:\t");

	int val;
	stack s;

	stack_new(&s, sizeof(int));
	for (val = 0; val < 6; val++) {
		stack_push(&s, &val);
		printf(" %i", val);
	}

	putchar('\n');
	printf("poped:\t");

	while (!stack_empty(&s)) {
		stack_pop(&s, &val);
		printf(" %i", val);
	}

	putchar('\n');

	stack_dispose(&s);
}

void 
str_stack() {
	printf("\nSTR STACK\n");
	printf("----------\n");

	stack s;
	char *ss[] = { "aa", "bb", "cc", "dd", "ee", "ff", 0 };
	
	printf("pushed:\t");

	stack_new(&s, sizeof(char*));
	char **p;	
	for (p = ss; *p != 0; p++) {
		stack_push(&s, p);
		printf(" %s", *p);	
	}
	
	putchar('\n');
	printf("poped:\t");
	
	while (!stack_empty(&s)) {
		stack_pop(&s, p);
		printf(" %s", *p);
	}	

	putchar('\n');
	
	stack_dispose(&s);
}

int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);
	
	int_stack();
	str_stack();
}
