#include <_memory_.h>
#include "stack.h"
#include <stdio.h>

#ifdef GCC
/* strdup is not standard C function */
#define __USE_SVID
#endif

#include <string.h>

void 
int_stack() {
	printf("\nINT STACK\n");
	printf("----------\n");
	printf("pushed:\t");

	int val;
	stack s;

	stack_new(&s, sizeof(int), 0);
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

	stack_new(&s, sizeof(char*), 0);
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

void
str_free(void *s) {
	free(*(char**)s);
}

void
str_dup_stack() {
	printf("\nSTR(dup) STACK\n");
	printf("----------\n");

	stack s;
	const char *ss[] = { "aa", "bb", "cc", "dd", "ee", "ff", 0 };
	
	printf("pushed:\t");

	stack_new(&s, sizeof(char*), str_free);
	const char **p;	
	for (p = ss; *p != 0; p++) {
		char *dup = strdup(*p);
		stack_push(&s, &dup);
		printf(" %s", *p);	
	}
	
	putchar('\n');
	printf("poped:\t");
	
	for (size_t i = 0; i < 3; i++) {
		stack_pop(&s, p);
		printf(" %s", *p);
		str_free(p);
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
	str_dup_stack();
}
