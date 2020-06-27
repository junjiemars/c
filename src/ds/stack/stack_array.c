#include "stack_array.h"
#include <stdlib.h>

static
void
node_new(stack_s *const stack) {
  stack->data = realloc(stack->data, (stack->n+1) * stack->size);
}

static
void
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

void
stack_push(stack_s *const stack, void *val, push_val push_val) {
  if (stack_full(stack)) {
    stack->n *= 2;
    size_t offset = (char*)stack->top - (char*)stack->data;
    node_new(stack);
    stack->top = (char*)stack->data + offset;
  }
  stack->top = (char*)stack->top + stack->size;
  push_val(stack, val);
}

int
stack_pop(stack_s *const stack, void *val, pop_val pop_val) {
  if (stack_empty(stack)) {
    return 0;
  }
  pop_val(stack, val);
  stack->top = (char*)stack->top - stack->size;
  return 1;
}
