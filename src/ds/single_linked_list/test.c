#include "single_linked_list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void
free_node(node_s *node) {
	if (0 == node) return;
	free(node);
}

node_s*
new_node(const void *val) {
	node_s *n = malloc(sizeof(node_s));
	assert(n);
	memset(n, 0, sizeof(node_s));

	n->val = val;
	return n;
}


void
test_static_str_list() {
  node_s *node = list_append(0, "Apple", new_node);
  node_s *head = node;
  assert((0 != head) && (0 == strcmp(head->val, "Apple")));

	list_append(node, "Bee", new_node);
  list_append(node, "Candy", new_node);
  
  free_node(head);
}

int
main() {
	test_static_str_list();
}
