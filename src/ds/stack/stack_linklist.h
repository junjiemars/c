#ifndef _STACK_LINKLIST_H_
#define _STACK_LINKLIST_H_

#include <stddef.h>


typedef struct node_s {
  void *data;
  struct node_s *next;
} node_s;

typedef struct stack_s {
  size_t size;
  node_s *top;
} stack_s;


int stack_empty(stack_s *const stack);

stack_s *stack_new(stack_s *stack, size_t size);
void stack_free(stack_s *stack);

void stack_push(stack_s *const stack, void *val);

int stack_pop(stack_s *const stack, void *val);


#endif /* end of _STACK_LINKLIST_H_ */
