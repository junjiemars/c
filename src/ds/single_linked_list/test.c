#include "single_linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void
free_node(node_s *node) {
  free(node);
}

void
free_alloc_node(node_s *node) {
	if (0 == node) return;
  free(node->val);
	free(node);
}

node_s*
new_node(void *val) {
	node_s *n = malloc(sizeof(node_s));
	assert(n);
	memset(n, 0, sizeof(node_s));

	n->val = val;
	return n;
}

int
node_str_cmp(const void *s1, const void *s2) {
  if (s1 && s2) {
    return strcmp(s1, s2);
  }
  return s1 - s2;
}

void
test_static_str_list() {
  node_s *head = list_append(0, "Apple", new_node);
  assert((0 != head) && (0 == strcmp(head->val, "Apple")));

	list_append(head, "Bee", new_node);
  list_append(head, "Candy", new_node);

  node_s *nil = list_find(0, "Bee", node_str_cmp);
  assert(0 == nil);

  node_s *tail = list_find(head, 0, node_str_cmp);
  assert(0 == tail);
  
  node_s *bee = list_find(head, "Bee", node_str_cmp);
  assert(0 == strcmp(bee->val, "Bee"));
  
  list_free(head, free_node);
}

int
main() {
	test_static_str_list();
}
