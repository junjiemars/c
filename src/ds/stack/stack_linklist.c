#include "stack_linklist.h"
#include <stdlib.h>


void
node_new(stack_s *const stack) {
  node_s *p = malloc(sizeof(node_s));
  p->data = malloc(stack->size);
  p->next = stack->top;
  stack->top = p;
}

static
void
node_free(node_s *node) {
  free(node->data);
  free(node);
}

stack_s*
stack_new(stack_s *stack, size_t size) {
  stack = calloc(1, sizeof(stack_s));
  if (stack) {
    stack->size = size;
  }
  return stack;
}

void
stack_free(stack_s *const stack) {
  if (!stack_empty(stack)) {
    node_s **p = &stack->top;
    do {
      node_s *next = (*p)->next;
      node_free(*p);
      *p = next;
    } while ((*p)->next);
  }

  free(stack);
}

int
stack_empty(stack_s *const stack) {
  return stack->top == 0;
}

void
stack_push(stack_s *const stack, void *val, push_val push_val) {
  node_new(stack);
  push_val(stack, val);
}

int
stack_pop(stack_s *const stack, void *val, pop_val pop_val) {
  if (stack_empty(stack)) {
    return 0;
  }
  pop_val(stack, val);
  node_s *top = stack->top;
  stack->top = stack->top->next;
  node_free(top);
  return 1;
}


/* eof */
