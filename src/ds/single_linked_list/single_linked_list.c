#include "single_linked_list.h"
#include <assert.h>


node_s*
list_append(node_s *head,
            void *val,
            node_s* (*new)(void *val)) {

  assert((0 != new) || "new fn cann not bu null");
  
  if (0 == head) {
    return head = new(val);
  } 

  while (0 != head->next) {
    head = head->next;
  }
  return head->next = new(val);
}

void
list_free(node_s *head,
          void (*free)(node_s *node)) {

  assert((0 != free) || "free fn can not be null");

  while (0 != head) {
    node_s *t = head;
    head = head->next;
    free(t);
  }
}

node_s*
list_find(node_s *head,
          const void *val,
          int (*cmp)(const void *val1, const void *val2)) {

  assert((0 != cmp) || "cmp fn can not be null");

  while (0 != head) {
    if (0 == cmp(head->val, val)) {
      return head;
    }
    head = head->next;
  }

  return 0;
}

void
list_delete(node_s **head,
            const void *val,
            int (*cmp)(const void *val1, const void* val2),
            void (*free)(node_s *node)) {

  assert((0 != cmp) || "cmp fn can not be null");
  assert((0 != free) || "free fn can not be null");

  for (node_s *curr=*head, *prev=0; curr; prev=curr, curr=curr->next) {

    if (0 == cmp(curr->val, val)) {

      if (0 == prev) {
        *head = curr->next;
      } else {
        prev->next = curr->next;
      }

      free(curr);
      return;
    }
  }
}

