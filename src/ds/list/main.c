#include <list.h>
#include <stdlib.h>

#define _unused_(x) ((void)(x))

void
free_node(list_node *node) {
	if (0 == node) return;

	free(node->data);
	free(node);
}

list_node*
new_node(void *data) {
	list_node *node = malloc(sizeof(list_node));
	if (0 == node) return 0;
	node->data = data;	

	return node;
}

int
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	list *lst = list_new(malloc(sizeof(list)));	

	int *i1 = malloc(sizeof(int));
	*i1 = 0;
	list_append(lst, new_node, i1);
	list_free(lst, free_node); 

	free(lst);
}
