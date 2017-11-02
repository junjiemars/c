
#ifndef _STACK_H_
#define _STACK_H_

/* include size_t declaration */
#include <stddef.h>

#ifndef STACK_INIT_CAPACITY
#	define STACK_INIT_CAPACITY 4ul
#endif


typedef struct {
	void *elements;
	void (*free_fn)(void *element);
	size_t width;
	size_t capacity;
	size_t top;
} stack;

void stack_new(stack *stack, size_t width, void (*free_fn)(void*));
void stack_dispose(stack *stack);
int stack_empty(const stack *stack);
void stack_push(stack *stack, const void *element);
void stack_pop(stack *stack, void *element);


#endif /* end of _STACK_H_ */
