
#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
#include <list.h>

typedef struct stack {
	size_t capacity;
	
	list* _c;

} stack;

typedef void (*stack_val_free)(void *val);

stack* stack_new(stack *alloc, size_t capacity);
stack* stack_free(stack *stack, stack_val_free free_val);


stack* stack_push(stack *stack, void *val);
stack* stack_pop(stack *stack, void **val);


#define stack_top(s) ((0 != (s) && (s)->_c && (s)->_c->head) \
	? ((s)->_c->head->val) : ((void*)0))

#define stack_size(s) ((0 != (s) && (s)->_c) ? (s)->_c->size : (0))

#define stack_empty(s) (0 == (s) || 0 == (s)->_c || 0 == (s)->_c->size)

#endif
