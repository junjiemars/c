#ifndef _STACK_H_
#define _STACK_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#define stack_empty(s) ((s)->top == (s)->data)
#define stack_full(s)                                                         \
  (((s)->n * s->width) == (size_t)((char *)(s)->top - (char *)(s)->data))
#define stack_capcity(s) ((s)->n)
#define stack_size(s) (((char *)((s)->top) - (char *)((s)->data)) / (s)->width)

typedef void (*stack_free_item_fn) (void *ptr);

typedef struct
{
  size_t n;
  size_t width;
  void *top;
  void *data;
  stack_free_item_fn free;
} stack_s;

stack_s *stack_new (stack_s *stack, size_t n, size_t width,
                    stack_free_item_fn free);
void stack_free (stack_s *const stack);
void *stack_push (stack_s *const stack, void *item);
void *stack_pop (stack_s *const stack, void *item);
void *stack_peek (stack_s *const stack, void *item);

stack_s *
stack_new (stack_s *stack, size_t n, size_t width, stack_free_item_fn free)
{
  if (NULL == stack)
    {
      return NULL;
    }

  stack->n = n;
  stack->width = width;
  stack->free = free;
  stack->top = stack->data = malloc (n * width);

  if (stack->top)
    {
      return stack;
    }
  return NULL;
}

void
stack_free (stack_s *const stack)
{
  if (NULL == stack)
    {
      return;
    }

  if (stack->free)
    {
      char *base = (char *)stack->data;
      char *top = (char *)stack->top;
      for (char **p = &base; *p < top; *p += stack->width)
        {
          stack->free (*p);
        }
    }
  free (stack->data);
}

void *
stack_push (stack_s *const stack, void *item)
{
  if (stack_full (stack))
    {
      size_t offset = (char *)stack->top - (char *)stack->data;
      stack->data = realloc (stack->data, stack->n * stack->width * 2);
      stack->top = (char *)stack->data + offset;
    }
  memcpy (stack->top, item, stack->width);
  stack->top = (char *)stack->top + stack->width;
  return item;
}

void *
stack_pop (stack_s *const stack, void *item)
{
  if (stack_empty (stack))
    {
      return NULL;
    }
  stack->top = (char *)stack->top - stack->width;
  memcpy (item, stack->top, stack->width);
  return item;
}

void *
stack_peek (stack_s *const stack, void *item)
{
  if (stack_empty (stack))
    {
      return NULL;
    }
  memcpy (item, (char *)stack->top - stack->width, stack->width);
  return item;
}

#endif /* end of _STACK_H_ */
