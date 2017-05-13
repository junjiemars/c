#include <list.h>
#include <stdlib.h>

void
free_node(list_node *node) {
	if (0 == node) return;
	
	free(node->data);
	free(node);
}

list_node*
new_node(void *data) {
	list_node *node = malloc(sizeof(list_node));
	node->data = data;
	return node;
}

void 
test_new_free_node() {
	char *s = malloc(64*sizeof(char));
	s[0] = 'N';	
	list_node *node = new_node(s);
	free_node(node);
}

void
test_new_free_list() {
	list* lst = list_new(malloc(sizeof(list)));
	list_free(lst, free_node);
	free(lst);
}

void
test_append() {
	list* lst = list_new(malloc(sizeof(list)));

	char *s1 = malloc(64*sizeof(char));
	s1[0] = 'A';
	list_append(lst, new_node, s1);
	
	char *s2 = malloc(64*sizeof(char));
	s2[0] = 'B';
	list_append(lst, new_node, s2);

	list_free(lst, free_node);
	free(lst);
}

int
main() {
	test_new_free_node();
	test_new_free_list();
	test_append();
}
