#include "node_array.h"
#include "stack.h"
#include <stdlib.h>

stack_s*
stack_new(stack_s *stack, new_node new_node, size_t n) {
  stack_s* s = realloc(stack, sizeof(stack_s));
  if (s) {
    s->node = new_node(0, n);
    s->n = n;
    s->top = s->node->data;
  }
  return s;
}

void
stack_free(stack_s *stack, free_node free_node) {
  free_node(stack->node);
  free(stack);
}

int
stack_empty(stack_s *const stack) {
  return stack->top == stack->node->data;
}

void
stack_push(stack_s *const stack,
           void *val,
           stack_full stack_full,
           new_node new_node,
           push_val push_val) {
  if (stack_full(stack)) {
    stack->n *= 2;
    new_node(stack->node, stack->n);
  }
  stack->top = push_val(stack, val);
}

int
stack_pop(stack_s *const stack,
          void *val,
          pop_val pop_val) {
  if (stack_empty(stack)) {
    return 0;
  }
  stack->top = pop_val(stack, val);
  return 1;
}
