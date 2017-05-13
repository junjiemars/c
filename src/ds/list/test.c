#include <list.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void
free_node(list_node *node) {
	if (0 == node) return;
	
	free(node->data);
	free(node);
}

list_node*
new_node(void *val) {
	list_node *node = malloc(sizeof(list_node));
	assert(node);
	memset(node, 0, sizeof(list_node));

	node->data = val;
	return node;
}

void 
test_new_free_node() {
	char *s = malloc(64*sizeof(char));
	assert(s);
	strcpy(s, "New node");	

	list_node *node = new_node(s);
	free_node(node);
}

void
test_new_free_list() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	list_free(lst, free_node);
	free(lst);
}

void
test_append() {
	list* lst = list_new(malloc(sizeof(list)));

	char *s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Apple");
	list_append(lst, s1, new_node);
	
	char *s2 = malloc(64*sizeof(char));
	assert(s2);
	strcpy(s2, "Bee");
	list_append(lst, s2, new_node);

	list_free(lst, free_node);
	free(lst);
}

void 
test_push() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	char *s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Apple"); 
	list_push(lst, s1, new_node);
	
	char *s2 = malloc(64*sizeof(char));
	assert(s2);
	strcpy(s2, "Bee");
	list_push(lst, s2, new_node);

	list_free(lst, free_node);
	free(lst);
}

void
test_remove() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	list_remove(lst, 0, free_node);

	char *s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Apple");
	list_append(lst, s1, new_node);
	list_remove(lst, s1, free_node);
	
	s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Again");
	list_append(lst, s1, new_node);

	char *s2 = malloc(64*sizeof(char));
	assert(s2);
	strcpy(s2, "Bee");
	list_append(lst, s2, new_node);

	list_remove(lst, s2, free_node);

	list_free(lst, free_node);
	free(lst);
}

int
main() {
	test_new_free_node();
	test_new_free_list();
	test_append();
	test_push();
	test_remove();
}
