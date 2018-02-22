#include "single_linked_list.h"
#include <assert.h>


node_s*
list_append(node_s *head,
            void *val,
            node_s* (*node_new)(void *val)) {

  assert(0 != node_new);
  
  if (0 == head) {
    return head = node_new(val);
  } 

  while (0 != head->next) {
    head = head->next;
  }
  return head->next = node_new(val);
}

void
list_free(node_s *head,
          void (*node_free)(node_s *node)) {
  assert(0 != node_free);

  while (0 != head) {
    node_s *current = head;
    head = head->next;
    node_free(current);
  }
}

node_s*
list_find(node_s *head,
          const void *val,
          int (*node_cmp)(const void *val1, const void *val2)) {

  assert((0 != node_cmp) || "node_cmp fn cannot be null");

  while (0 != head) {
    if (0 == node_cmp(head->val, val)) {
      return head;
    }
    head = head->next;
  }

  return 0;
}
