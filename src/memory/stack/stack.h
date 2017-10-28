
#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>

#ifndef STACK_INIT_SIZE
#define STACK_INIT_SIZE 4ul
#endif

typedef struct {
	void *elems;
	void (*free_fn)(void *elem_addr);
	size_t elem_size;
	size_t log_length;
	size_t alloc_length;
} stack;

void stack_new(stack *s, size_t elem_size, void (*free_fn)(void*));
void stack_dispose(stack *s);
int stack_empty(const stack *s);
void stack_push(stack *s, const void *elem_addr);
void stack_pop(stack *s, void *elem_addr);

#endif /* end of _STACK_H_ */
