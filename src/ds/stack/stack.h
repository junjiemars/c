#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>

typedef struct node_s {
  void *data;
} node_s;

typedef struct stack_s {
	size_t n;
  size_t size;
  void *top;
  node_s node;
} stack_s;

#ifndef _unused_
#define _unused_(x) ((void)(x))
#endif

void node_new(stack_s *const stack);
void node_free(stack_s *const stack);

stack_s* stack_new(stack_s *stack, size_t n, size_t size);
void stack_free(stack_s *const stack);

int stack_empty(stack_s *const stack);
int stack_full(stack_s *const stack);

typedef void (*push_val)(stack_s *const stack, void *val);
typedef void (*pop_val)(stack_s *const stack, void *val);

void stack_push(stack_s *const stack, void *val, push_val push_val);

int stack_pop(stack_s *const stack, void *val, pop_val pop_val);


/* #define stack_top(s) ((0 != (s) && (s)->_c && (s)->_c->head) \ */
/* 	? ((s)->_c->head->val) : ((void*)0)) */

/* #define stack_size(s) ((0 != (s) && (s)->_c) ? (s)->_c->size : (0)) */

/* #define stack_empty(s) (0 == (s) || 0 == (s)->_c || 0 == (s)->_c->size) */

#endif /* end of _STACK_H_ */
