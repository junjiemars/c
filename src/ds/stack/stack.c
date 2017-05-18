#include <stack.h>
#include <stdlib.h>
#include <string.h>

node*
new_node(void *val) {
	node *n = malloc(sizeof(node));
	memset(n, 0, sizeof(node));

	n->val = val;
	return n;
}

void
free_node(node *node) {
	free(node);
}

stack*
stack_new(stack *alloc, size_t capacity) {
	if (0 == alloc) return 0;

	alloc->capacity = capacity;
	alloc->_c = list_new(malloc(sizeof(list)));

	return alloc;	
}

stack* 
stack_free(stack *stack, stack_val_free free_val) {
	if (0 == stack || 0 == free_val) return 0;
	
	while (stack_top(stack)) {
		void *n;
		stack_pop(stack, &n);
		free_val(n);
	}
	
	return 0;		
}

stack*
stack_push(stack *stack, void *val) {
	if (0 == stack) return 0;

	list_push(stack->_c, val, new_node);
	return stack;	
}

stack*
stack_pop(stack *stack, void **val) {
	if (0 == stack) return 0;
	if (list_empty(stack->_c)) {
		_unused_(val);
		return 0;
	}

	node *tail;
	if (list_remove_tail(stack->_c, &tail)) {
		val = &tail->val;
		free(tail);
		return stack;
	}
	
	return stack;
}
