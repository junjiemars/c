#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>


#if !defined(SORT) || (SORT) < 0
#  define _sort_(expr) ((expr) < 0)
#else
#  define _sort_(expr) ((expr) >= 0)
#endif


typedef struct node_s {
  void *data;
  struct node_s *next;
} node_s;

typedef struct list_s {
  size_t size;
  struct node_s *head;
} list_s;


node_s *list_node_new(list_s *const l);
void list_node_free(node_s *const n);

list_s *list_new(list_s *l, size_t size);
void list_free(list_s *const l);


node_s *list_insert(list_s *const l, void *val,
                    int (*cmp)(const void *lhs, const void *rhs));

node_s *list_find(list_s *const l, const void *val,
                  int (*cmp)(const void *lhs, const void *rhs));

int list_remove(list_s *const l, node_s *const n);


inline node_s*
list_node_new(list_s *const l)
{
  node_s *n = calloc(1, sizeof(node_s));
  if (n) {
    n->data = malloc(l->size);
  }
  return n;
}

inline void
list_node_free(node_s *const n)
{
  if (n) {
    free(n->data);
    free(n);
  }
}

list_s*
list_new(list_s *l, size_t size)
{
  l = calloc(1, sizeof(list_s));
  if (l) {
    l->size = size;
  }
  return l;
}

void
list_free(list_s *const l)
{
  node_s *h = l->head;
  node_s *c;
  while (h) {
    c = h;
    h = h->next;
    list_node_free(c);
  }
  free(l);
}

node_s*
list_insert(list_s *const l, void *val,
            int (*cmp)(const void *lhs, const void *rhs))
{
  node_s *new_one = list_node_new(l);
  if (!new_one) {
    return 0;
  }
  memcpy(new_one->data, val, l->size);

  node_s *h = l->head;
  node_s *pre = 0;
  while (h && !_sort_(cmp(val, h->data))) {
    pre = h;
    h = h->next;
  }

  new_one->next = h;
  if (pre) {
    pre->next = new_one;
  } else {
    l->head = new_one;
  }

  return new_one;
}

node_s
*list_find(list_s *const l, const void *val,
                  int (*cmp)(const void *lhs, const void *rhs))
{
  if (_sort_(cmp(val, l->head->data))) {
    return 0;
  }
  
  node_s *h = l->head->next;
  while (h && 0 != cmp(val, h->data)) {
    h = h->next;
  }
  return h;
}

int
list_remove(list_s *const l, node_s *const n)
{
  node_s *h = l->head;
  node_s *pre = 0;
  while (h) {
    if (h == n) {
      if (pre) {
        pre->next = h->next;
      } 
      list_node_free(h);
      return 1;
    }
    pre = h;
    h = h->next;
  }
  return 0;
}

#endif /* end of _LIST_H_ */
