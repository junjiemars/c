
#ifndef _STACK_H_
#define _STACK_H_

#include <stdlib.h>


typedef struct {
	void *elems;
	size_t elem_size;
	size_t log_length;
	size_t alloc_length;
} stack;

void stack_new(stack *s, size_t elem_size);
void stack_dispose(stack *s);
int stack_empty(const stack *s);
void stack_push(stack *s, const void *elem_addr);
void stack_pop(stack *s, void *elem_addr);

#endif /* end of _STACK_H_ */
