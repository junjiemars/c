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

int
comp_int_node(void *lhs, void *rhs) {
	int *l = lhs;
	int *r = rhs;
	
	if (*l == *r) return 0;
	else if (*l < *r) return -1;
	else return 1; 	
}

int
comp_str_node(void *lhs, void *rhs) {
	char *l = lhs;
	char *r = rhs;
	return strcmp(l, r);
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

	list_remove(lst, 0, comp_str_node, free_node);

	char *s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Apple");
	list_append(lst, s1, new_node);
	list_remove(lst, s1, comp_str_node, free_node);
	
	s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Again");
	list_append(lst, s1, new_node);

	char *s2 = malloc(64*sizeof(char));
	assert(s2);
	strcpy(s2, "Bee");
	list_append(lst, s2, new_node);

	list_remove(lst, s2, comp_str_node, free_node);

	list_free(lst, free_node);
	free(lst);
}

void 
test_find() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	int *i1 = malloc(sizeof(int));
	assert(i1);
	*i1 = 1;
	list_append(lst, i1, new_node);
	
	int *i2 = malloc(sizeof(int));
	assert(i2);
	*i2 = 2;
	list_append(lst, i2, new_node);

	list_node *node = list_find(lst, i1, comp_int_node);
	assert(node);

	list_free(lst, free_node);
	free(lst);	
}

void
test_insert() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	list_node *n;

	int *i1 = malloc(sizeof(int));
	assert(i1);
	*i1 = 1;
	n = list_append(lst, i1, new_node);
	assert(n);

	int *i2 = malloc(sizeof(int));
	assert(i2);
	*i2 = 2;
	n = list_insert(lst, n, i2, new_node);
	if (0 == n) free(i2);
	assert(2 == *(int*)n->data);
	
	int *i3 = malloc(sizeof(int));
	assert(i3);
	*i3 = 3;
	n = list_insert(lst, lst->head, i3, new_node);
	if (0 == n) free(i3);
	assert(3 == *(int*)n->data);
	
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
	test_find();
	test_insert();
}
