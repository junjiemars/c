#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
  char data[sizeof(char*)];
  struct node_s *next;
} node_s;

typedef struct list_s {
  size_t size;
  struct node_s *head;
  struct node_s *tail;
} list_s;


static node_s *list_node_new(void);
static void list_node_free(node_s *const n);

list_s *list_new(list_s *l, size_t size);
void list_free(list_s *const l);

node_s *list_append(list_s *const l, void *val);
node_s *list_find(list_s *const l, const void *val,
                  int (*cmp)(const void *lhs, const void *rhs));
int list_remove(list_s *const l, node_s *const n);

static inline node_s*
list_node_new(void) {
  node_s *n = calloc(1, sizeof(node_s));
  return n;
}

static inline void
list_node_free(node_s *const n) {
  free(n);
}

list_s*
list_new(list_s *l, size_t size) {
  l = calloc(1, sizeof(list_s));
  if (l) {
    l->size = size;
  }
  return l;
}

void
list_free(list_s *const l) {
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
list_append(list_s *const l, void *val) {
  node_s *new_one = list_node_new();
  if (!new_one) {
    return 0;
  }
  memcpy(new_one->data, val, l->size);
  
  if (!l->head) {
    l->head = l->tail = new_one;
  } else {
    l->tail = l->tail->next = new_one;
  }

  return l->tail;
}

node_s*
list_find(list_s *const l, const void *val,
          int (*cmp)(const void *lhs, const void *rhs)) {
  node_s *h = l->head;
  while (h) {
    if (0 == cmp(h->data, val)) {
      return h;
    }
    h = h->next;
  }
  return 0;
}

int
list_remove(list_s *const l, node_s *const n) {
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
