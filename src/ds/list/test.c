#include <list.h>
#include <ds.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void
free_node(list_node *node) {
	if (0 == node) return;
	
	free(node->val);
	free(node);
}

list_node*
new_node(void *val) {
	list_node *node = malloc(sizeof(list_node));
	assert(node);
	memset(node, 0, sizeof(list_node));

	node->val = val;
	return node;
}

int
cmp_int_node(void *lhs, void *rhs) {
	int *l = lhs;
	int *r = rhs;
	
	if (*l == *r) return 0;
	else if (*l < *r) return -1;
	else return 1; 	
}

int
cmp_str_node(void *lhs, void *rhs) {
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

	free(list_free(lst, free_node));
}

void
test_append() {
	list* lst = list_new(malloc(sizeof(list)));

	list_node *n;

	char *s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Apple");
	n = list_append(lst, s1, new_node);
	assert(lst->tail == n && 0 == strcmp("Apple", (char*)n->val));
	
	char *s2 = malloc(64*sizeof(char));
	assert(s2);
	strcpy(s2, "Bee");
	n = list_append(lst, s2, new_node);
	assert(lst->tail == n && 0 == strcmp("Bee", (char*)n->val));

	lst = list_free(lst, free_node);
	assert(0 == list_size(lst));
	free(lst);
}

void 
test_push() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	list_node *n;

	char *s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Apple"); 
	n = list_push(lst, s1, new_node);
	assert(0 == strcmp("Apple", (char*)n->val));
	assert(0 == strcmp("Apple", (char*)lst->head->val));
	
	char *s2 = malloc(64*sizeof(char));
	assert(s2);
	strcpy(s2, "Bee");
	n = list_push(lst, s2, new_node);
	assert(0 == strcmp("Bee", (char*)n->val));
	assert(0 == strcmp("Bee", (char*)lst->head->val));
	assert(0 == strcmp("Apple", (char*)lst->tail->val));

	free(list_free(lst, free_node));
}

void
test_remove() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	list_node *a, *n;
	
	n = list_remove(lst, 0, cmp_str_node);
	assert(0 == n);

	char *s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Apple");
	a = list_append(lst, s1, new_node);
	n = list_remove(lst, s1, cmp_str_node);
	assert(a == n && 0 == strcmp("Apple", (char*)n->val));
	free_node(n);
	
	s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Again");
	list_append(lst, s1, new_node);

	char *s2 = malloc(64*sizeof(char));
	assert(s2);
	strcpy(s2, "Bee");
	a = list_append(lst, s2, new_node);

	n = list_remove(lst, s2, cmp_str_node);
	assert(a == n && 0 == strcmp("Bee", (char*)n->val));
	free_node(n);

	free(list_free(lst, free_node));
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

	list_node *node = list_find(lst, i1, cmp_int_node);
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
	n = list_insert(lst, 0, i1, new_node);
	if (0 == n) free(i1);
	assert(*i1 == *(int*)n->val);

	int *i2 = malloc(sizeof(int));
	assert(i2);
	*i2 = 2;
	n = list_insert(lst, n, i2, new_node);
	if (0 == n) free(i2);
	assert(*i2 == *(int*)n->val);
	
	int *i3 = malloc(sizeof(int));
	assert(i3);
	*i3 = 3;
	n = list_insert(lst, lst->head, i3, new_node);
	if (0 == n) free(i3);
	assert(*i3 == *(int*)n->val);

	int *i4 = malloc(sizeof(int));
	assert(i4);
	*i4 = 4;
	n = list_insert(lst, lst->tail, i4, new_node);
	if (0 == n) free(i4);
	assert(*i4 == *(int*)n->val);	
	
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
