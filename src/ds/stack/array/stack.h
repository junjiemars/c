#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


typedef struct stack_s {
	size_t n;
  size_t size;
  void *top;
  void *data;
} stack_s;


static inline void*
node_new(stack_s *const stack) {
  return stack->data = realloc(stack->data, (stack->n+1) * stack->size);
}

static inline void
node_free(stack_s *const stack) {
  free(stack->data);
}


stack_s*
stack_new(stack_s *stack, size_t n, size_t size) {
  stack = calloc(1, sizeof(stack_s));
  if (stack) {
    stack->size = size;
    stack->n = n;
    node_new(stack);
    stack->top = stack->data;
  }
  return stack;  
}

void
stack_free(stack_s *const stack) {
  node_free(stack);
  free(stack);  
}

int
stack_empty(stack_s *const stack) {
  return stack->top == stack->data;  
}

int
stack_full(stack_s *const stack) {
  size_t len = (char*)stack->top - (char*)stack->data;
  return stack->size * stack->n == len;  
}

void*
stack_push(stack_s *const stack, void *val) {
  if (stack_full(stack)) {
    stack->n *= 2;
    size_t offset = (char*)stack->top - (char*)stack->data;
    void *new_one = node_new(stack);
    if (0 == new_one) {
      return 0;
    }
    stack->top = (char*)stack->data + offset;
  }
  stack->top = (char*)stack->top + stack->size;
  memcpy(stack->top, val, stack->size);  
  return stack->top;
}

void*
stack_pop(stack_s *const stack, void *val) {
  if (stack_empty(stack)) {
    return 0;
  }
  memcpy(val, stack->top, stack->size);
  return stack->top = (char*)stack->top - stack->size;
}


#endif /* end of _STACK_H_ */
