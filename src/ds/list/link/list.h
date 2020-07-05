#ifndef _LIST_H_
#define _LIST_H_

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
  void *data;
  struct node_s *next;
} node_s;

typedef struct list_s {
  size_t size;
  struct node_s *head;

#if !defined(SORT)
  struct node_s *tail;
#endif
} list_s;


node_s *list_node_new(list_s *const l);
void list_node_free(node_s *const n);

list_s *list_new(list_s *l, size_t size);
void list_free(list_s *const l);

#if defined(SORT)

#if (SORT) >= 0
#  define _sort_(expr) ((expr) >= 0)
#else
#  define _sort_(expr) ((expr) < 0)
#endif

node_s *list_insert(list_s *const l, void *val,
                    int (*cmp)(const void *lhs, const void *rhs));
node_s *list_find(list_s *const l, const void *val,
                  int (*cmp)(const void *lhs, const void *rhs));
#else

node_s *list_append(list_s *const l, void *val);
node_s *list_prepend(list_s *const l, void *val);
node_s *list_find(list_s *const l, const void *val,
                  int (*cmp)(const void *lhs, const void *rhs));

#endif /* end of defined(SORT) */

int list_remove(list_s *const l, node_s *const n);

inline node_s*
list_node_new(list_s *const l) {
  node_s *n = calloc(1, sizeof(node_s));
  if (n) {
    n->data = malloc(l->size);
  }
  return n;
}

inline void
list_node_free(node_s *const n) {
  if (n) {
    free(n->data);
    free(n);
  }
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

#if defined(SORT)

node_s*
list_insert(list_s *const l, void *val,
            int (*cmp)(const void *lhs, const void *rhs)) {
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
#endif /* end of defined(SORT) */

#if defined(SORT)
node_s *list_find(list_s *const l, const void *val,
                  int (*cmp)(const void *lhs, const void *rhs)) {
  if (_sort_(cmp(val, l->head->data))) {
    return 0;
  }
  
  node_s *h = l->head->next;
  while (h && 0 != cmp(val, h->data)) {
    h = h->next;
  }
  return h;
}
#endif /* end of defined(SORT) */

#if !defined(SORT)
node_s*
list_append(list_s *const l, void *val) {
  node_s *new_one = list_node_new(l);
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
#endif /* end of SORT */

#if !defined(SORT)

node_s*
list_prepend(list_s *const l, void *val) {
  node_s *new_one = list_node_new(l);
  if (!new_one) {
    return 0;
  }
  memcpy(new_one->data, val, l->size);

  if (!l->head) {
    l->head = l->tail = new_one;
  } else {
    new_one->next = l->head;
    l->head = new_one;
  }
  
  return l->head;
}
#endif /* end of SORT */


#if !defined(SORT)

node_s*
list_find(list_s *const l, const void *val,
          int (*cmp)(const void *lhs, const void *rhs)) {
  node_s *h = l->head;
  while (h) {
    if (0 == cmp(val, h->data)) {
      return h;
    }
    h = h->next;
  }
  return 0;
}
#endif /* end of SORT */

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
