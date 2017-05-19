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
stack_free(stack *s, stack_val_free free_val) {
	if (0 == s || 0 == free_val) return 0;
	
	while (!stack_empty(s)) {
		void *n = 0;
		stack_pop(s, &n);
		free_val(n);
	}

	free(list_free(s->_c, free_node));
	s->_c = 0;
	
	return s;		
}

stack*
stack_push(stack *s, void *val) {
	if (0 == s || stack_size(s) == s->capacity) return 0;

	list_push(s->_c, val, new_node);
	return s;	
}

void
stack_pop(stack *s, void **val) {
	if (0 == s || 0 == val) return;

	if (list_empty(s->_c)) {
		_unused_(val);
		return;
	}

	node *tail = 0;
	if (list_remove_tail(s->_c, &tail)) {
		*val = tail->val;
		free_node(tail);
		return;
	}
}
