#include "stack.h"
#include <ds.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


void 
free_str(void *val) {
  if (0 == val) return;
  free(*(char**)&val);
}

void
test_new_free() {
	stack s;
	stack_new(&s, 4); 
	stack_free(&s, free_str);
	
	stack *s1 = malloc(sizeof(stack));
	assert(s1);
	stack_new(s1, 4);
	stack_free(s1, free_str);
    free(s1);
}

void 
test_push() {
  stack s;
  stack_new(&s, 4);

  char *ss[] = {"Al", "Bob", "Cat", 0};
  for (char **p = ss; *p; p++) {
    char *c = malloc(16*sizeof(char*));
		assert(c);

		c = strcpy(c, *p);	
		assert(c);

    stack_push(&s, c);
  }

  stack_free(&s, free_str);
}

void
test_push_pop() {
	stack *s = stack_new(malloc(sizeof(stack)), 4);

  char *ss[] = {"Al", "Bob", "Cat", "Eva", "Frank", 0};
  for (char **p = ss; *p; p++) {
    char *c = malloc(16*sizeof(char*));
		c = strcpy(c, *p);	
    stack_push(s, c);
		printf("push => %s\n", c);
  }

	char *name;
	while (stack_empty(s)) {
		stack_pop(s, (void**)&name);
		printf("pop => %s\n", name);
	}

	free(stack_free(s, &free_str));
}

int
main() {
	test_new_free();
	test_push();
	test_push_pop();
}
