#ifndef QUEUE_H_
#define QUEUE_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


#define queue_empty(q)  ((q)->head == (q)->tail)
#define queue_full(q)  \
  (((q)->n * (q)->width) == (size_t)((char*)(q)->tail - (char*)(q)->data))
#define queue_capcity(q)  ((q)->n)
#define queue_size(q)  ((size_t)((char*)(q)->tail - (char*)(q)->head) / (q)->width)


typedef void (*free_fn)(void *ptr);


typedef struct {
  size_t    n;
  size_t    width;
  free_fn   free;
  void     *head;
  void     *tail;
  void     *data;
} queue_s;


queue_s *queue_new(queue_s *q, size_t n, size_t width, free_fn free);
void queue_free(queue_s *const q);
void *queue_enq(queue_s *const q, void *item);
void *queue_deq(queue_s *const q, void *item);
void *queue_peek(queue_s *const q, void *item);


queue_s *
queue_new(queue_s *q, size_t n, size_t width, free_fn free)
{
  if (NULL == q)
    {
      return NULL;
    }

  q->n = n;
  q->width = width;
  q->free = free;
  q->head = q->tail = q->data = malloc(n * width);

  if (q->head)
    {
      return q;
    }
  return NULL;
}

void queue_free(queue_s *const q)
{
  char  *head;
  char  *tail;

  if (NULL == q)
    {
      return;
    }

  if (q->free)
    {
      head = (char *) q->head;
      tail = (char *) q->tail;

      for (char **p = &head; *p < tail; *p += q->width)
        {
          q->free(*p);
        }
    }
  
  free(q->data);
}

void *
queue_enq(queue_s *const q, void *item)
{
  size_t  offset;
  size_t  len;
  size_t  n;
  
  if (queue_full(q))
    {
      offset = (char *) q->head - (char *) q->data;
      len = (char *) q->tail - (char *) q->head;

      if (offset > 0)
        {
          memmove(q->data, q->head, len);
        }
      else
        {
          n = q->n * 2;
          q->data = realloc(q->data, n * q->width);
          q->n = n;
        }
      q->head = q->data;
      q->tail = (char *) q->head + len;
    }

  memcpy(q->tail, item, q->width);
  q->tail = (char *) q->tail + q->width;
  return item;
}

void *
queue_deq(queue_s *const q, void *item)
{
  if (queue_empty(q))
    {
      return NULL;
    }

  memcpy(item, q->head, q->width);
  q->head = (char *) q->head + q->width;
  return item;
}

void *
queue_peek(queue_s *const q, void *item)
{
  if (queue_empty(q))
    {
      return NULL;
    }

  memcpy(item, q->head, q->width);
  return item;
}


#endif /* end of QUEUE_H_ */
