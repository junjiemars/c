#include "_ds_.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void
free_node(node *node) {
	if (0 == node) return;
	
	free(node->val);
	free(node);
}

node*
new_node(void *val) {
	node *n = malloc(sizeof(node));
	ASSERT(n);
	memset(n, 0, sizeof(node));

	n->val = val;
	return n;
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
	ASSERT(s);
	strcpy(s, "New node");	

	node *node = new_node(s);
	free_node(node);
}

void
test_new_free_list() {
	list* lst = list_new(malloc(sizeof(list)));
	ASSERT(lst);

	free(list_free(lst, free_node));
}

void
test_append() {
	list* lst = list_new(malloc(sizeof(list)));

	node *n;
  _unused_(n);

	char *s1 = malloc(64*sizeof(char));
	ASSERT(s1);
	strcpy(s1, "Apple");
	n = list_append(lst, s1, new_node);
	ASSERT(lst->tail == n && 0 == strcmp("Apple", (char*)n->val));
	
	char *s2 = malloc(64*sizeof(char));
	ASSERT(s2);
	strcpy(s2, "Bee");
	n = list_append(lst, s2, new_node);
	ASSERT(lst->tail == n && 0 == strcmp("Bee", (char*)n->val));

	lst = list_free(lst, free_node);
	ASSERT(0 == list_size(lst));
	free(lst);
}

void 
test_push() {
	list* lst = list_new(malloc(sizeof(list)));
	ASSERT(lst);

	node *n;
  _unused_(n);

	char *s1 = malloc(64*sizeof(char));
	ASSERT(s1);
	strcpy(s1, "Apple"); 
	n = list_push(lst, s1, new_node);
	ASSERT(0 == strcmp("Apple", (char*)n->val));
	ASSERT(0 == strcmp("Apple", (char*)lst->head->val));
	
	char *s2 = malloc(64*sizeof(char));
	ASSERT(s2);
	strcpy(s2, "Bee");
	n = list_push(lst, s2, new_node);
	ASSERT(0 == strcmp("Bee", (char*)n->val));
	ASSERT(0 == strcmp("Bee", (char*)lst->head->val));
	ASSERT(0 == strcmp("Apple", (char*)lst->tail->val));

	free(list_free(lst, free_node));
}

void
test_remove_val() {
	list* lst = list_new(malloc(sizeof(list)));
	ASSERT(lst);

	node *a, *n;
  _unused_(a);
  _unused_(n);
	
	n = list_remove_val(lst, 0, cmp_str_node);
	ASSERT(0 == n);

	char *s1 = malloc(64*sizeof(char));
	ASSERT(s1);
	strcpy(s1, "Apple");
	a = list_append(lst, s1, new_node);
	n = list_remove_val(lst, s1, cmp_str_node);
	ASSERT(a == n && 0 == strcmp("Apple", (char*)n->val));
	free_node(n);
	
	s1 = malloc(64*sizeof(char));
	ASSERT(s1);
	strcpy(s1, "Again");
	list_append(lst, s1, new_node);

	char *s2 = malloc(64*sizeof(char));
	ASSERT(s2);
	strcpy(s2, "Bee");
	a = list_append(lst, s2, new_node);

	n = list_remove_val(lst, s2, cmp_str_node);
	ASSERT(a == n && 0 == strcmp("Bee", (char*)n->val));
	free_node(n);

	free(list_free(lst, free_node));
}

void
test_remove_next() {
	list *lst = list_new(malloc(sizeof(list)));
	ASSERT(lst);

	char *s1 = malloc(64*sizeof(char));
	strcpy(s1, "Apple");
	node *n1 = list_append(lst, s1, new_node);
  _unused_(n1);
	ASSERT(n1);

	char *s2 = malloc(64*sizeof(char));
	strcpy(s2, "Bear");
	node *n2 = list_append(lst, s2, new_node);
	ASSERT(n2);

	char *s3 = malloc(64*sizeof(char));
	strcpy(s3, "Code");
	node *n3 = list_append(lst, s3, new_node);
	ASSERT(n3);
	ASSERT(lst->tail == n3);

	node *removed = list_remove_next(lst, n3);
	ASSERT(0 == removed);

	removed = list_remove_next(lst, n2);
	ASSERT(removed);
	ASSERT(list_tail(lst) == n2);
	free_node(removed);

	removed = list_remove_next(lst, lst->head);
	ASSERT(removed);
	ASSERT(removed == n2);
	free_node(removed);

	free(list_free(lst, free_node));
}

void
test_remove_tail() {
	list *lst = list_new(malloc(sizeof(list)));
	ASSERT(lst);

	char *s1 = malloc(64*sizeof(char));
	strcpy(s1, "Apple");
	node *n1 = list_append(lst, s1, new_node);
  _unused_(n1);
	ASSERT(n1);

	char *s2 = malloc(64*sizeof(char));
	strcpy(s2, "Bear");
	node *n2 = list_append(lst, s2, new_node);
  _unused_(n2);
	ASSERT(n2);

	char *s3 = malloc(64*sizeof(char));
	strcpy(s3, "Code");
	node *n3 = list_append(lst, s3, new_node);
  _unused_(n3);
	ASSERT(n3);
	ASSERT(lst->tail == n3);

	node *tail = 0;
	while(!list_empty(lst)) {
		free_node(list_remove_tail(lst, &tail));
	}
	
	free(list_free(lst, free_node));
}

void 
test_find() {
	list* lst = list_new(malloc(sizeof(list)));
	ASSERT(lst);

	int *i1 = malloc(sizeof(int));
	ASSERT(i1);
	*i1 = 1;
	list_append(lst, i1, new_node);
	
	int *i2 = malloc(sizeof(int));
	ASSERT(i2);
	*i2 = 2;
	list_append(lst, i2, new_node);

	node *node = list_find(lst, i1, cmp_int_node);
  _unused_(node);
	ASSERT(node);

	list_free(lst, free_node);
	free(lst);	
}

void
test_insert() {
	list* lst = list_new(malloc(sizeof(list)));
	ASSERT(lst);

	node *n;

	int *i1 = malloc(sizeof(int));
	ASSERT(i1);
	*i1 = 1;
	n = list_insert(lst, 0, i1, new_node);
	if (0 == n) free(i1);
	ASSERT(*i1 == *(int*)n->val);

	int *i2 = malloc(sizeof(int));
	ASSERT(i2);
	*i2 = 2;
	n = list_insert(lst, n, i2, new_node);
	if (0 == n) free(i2);
	ASSERT(*i2 == *(int*)n->val);
	ASSERT(2 == list_size(lst));
	ASSERT(lst->head != lst->tail);
	
	int *i3 = malloc(sizeof(int));
	ASSERT(i3);
	*i3 = 3;
	n = list_insert(lst, lst->head, i3, new_node);
	if (0 == n) free(i3);
	ASSERT(*i3 == *(int*)n->val);

	int *i4 = malloc(sizeof(int));
	ASSERT(i4);
	*i4 = 4;
	n = list_insert(lst, lst->tail, i4, new_node);
	if (0 == n) free(i4);
	ASSERT(*i4 == *(int*)n->val);	
	
	list_free(lst, free_node);
	free(lst);	
}

int
main() {
	test_new_free_node();
	test_new_free_list();
	test_append();
	test_push();
	test_remove_val();
	test_remove_next();
	test_remove_tail();
	test_find();
	test_insert();
}
