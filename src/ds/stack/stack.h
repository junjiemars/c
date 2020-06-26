#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
/* #include "double_linked_list/list.h" */

typedef struct stack_s {
	size_t n;
  void *top;
  node_s *node;
	/* list* _c; */

} stack_s;

#ifndef _unused_
#define _unused_(x) ((void)(x))
#endif

typedef node_s* (*new_node)(node_s *node, size_t n);
typedef void (*free_node)(node_s *node);

stack_s* stack_new(stack_s *stack, new_node new_node, size_t n);
void stack_free(stack_s *stack, free_node free_node);

int stack_empty(stack_s *const stack);

typedef int (*stack_full)(stack_s *const stack);
typedef void* (*push_val)(stack_s *const stack, void *val);
typedef void* (*pop_val)(stack_s *const stack, void *val);

void stack_push(stack_s *const stack,
                void *val,
                stack_full stack_full,
                new_node new_node,
                push_val push_val);

void stack_pop(stack_s *const stack,
               void *val,
               pop_val pop_val);


/* #define stack_top(s) ((0 != (s) && (s)->_c && (s)->_c->head) \ */
/* 	? ((s)->_c->head->val) : ((void*)0)) */

/* #define stack_size(s) ((0 != (s) && (s)->_c) ? (s)->_c->size : (0)) */

/* #define stack_empty(s) (0 == (s) || 0 == (s)->_c || 0 == (s)->_c->size) */

#endif /* end of _STACK_H_ */
