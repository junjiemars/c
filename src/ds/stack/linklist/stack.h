#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s
{
  void *data;
  struct node_s *next;
} node_s;

typedef struct stack_s
{
  size_t size;
  node_s *top;
} stack_s;

static inline void *
stack_node_new (stack_s *const stack)
{
  node_s *p = malloc (sizeof (node_s));
  if (0 == p)
    {
      return 0;
    }
  p->data = malloc (stack->size);
  p->next = stack->top;
  return stack->top = p;
}

static inline void
stack_node_free (node_s *node)
{
  free (node->data);
  free (node);
}

int
stack_empty (stack_s *const stack)
{
  return stack->top == 0;
}

stack_s *
stack_new (stack_s *stack, size_t size)
{
  stack = calloc (1, sizeof (stack_s));
  if (stack)
    {
      stack->size = size;
    }
  return stack;
}

void
stack_free (stack_s *stack)
{
  if (!stack_empty (stack))
    {
      node_s **p = &stack->top;
      do
        {
          node_s *next = (*p)->next;
          stack_node_free (*p);
          *p = next;
        }
      while ((*p)->next);
    }

  free (stack);
}

void *
stack_push (stack_s *const stack, void *val)
{
  void *new_one = stack_node_new (stack);
  if (0 == new_one)
    {
      return 0;
    }
  memcpy (stack->top->data, val, stack->size);
  return val;
}

void *
stack_pop (stack_s *const stack, void *val)
{
  if (stack_empty (stack))
    {
      return 0;
    }
  memcpy (val, stack->top->data, stack->size);
  node_s *old_one = stack->top;
  stack->top = stack->top->next;
  stack_node_free (old_one);
  return val;
}

void *
stack_peek (stack_s *const stack, void *val)
{
  if (stack_empty (stack))
    {
      return 0;
    }
  memcpy (val, stack->top->data, stack->size);
  return val;
}

#endif /* end of _STACK_H_ */
