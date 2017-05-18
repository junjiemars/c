#include "stack.h"
#include <ds.h>
#include <stdlib.h>
#include <assert.h>

void 
free_val(void *val) {
	free(val);
}

void
test_new_free() {
	stack s;
	stack_new(&s, 4); 
	stack_free(&s, free_val);
	
	stack *s1 = malloc(sizeof(stack));
	assert(s1);
	stack_new(s1, 4);
	stack_free(s1, free_val);
}

int
main() {
	test_new_free();
}
