#include "_ds_.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


void
free_node(node *node)
{
	if (0 == node) return;

	free(node->val);
	free(node);
}

node*
new_node(void *val)
{
	node *n = malloc(sizeof(node));
	assert(n);
	memset(n, 0, sizeof(node));

	n->val = val;
	return n;
}

int
cmp_int_node(void *lhs, void *rhs)
{
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
test_new_free_node()
{
	char *s = malloc(64*sizeof(char));
	assert(s);
	strcpy(s, "New node");

	node *node = new_node(s);
	free_node(node);
}

void
test_new_free_list() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	free(list_free(lst, free_node));
}

void
test_append()
{
	list* lst = list_new(malloc(sizeof(list)));

	__attribute__((unused)) node *n;

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
test_push()
{
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	__attribute__((unused)) node *n;

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
test_remove_val()
{
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	__attribute__((unused)) node *a;
  __attribute__((unused)) node *n;

	n = list_remove_val(lst, 0, cmp_str_node);
	assert(0 == n);

	char *s1 = malloc(64*sizeof(char));
	assert(s1);
	strcpy(s1, "Apple");
	a = list_append(lst, s1, new_node);
	n = list_remove_val(lst, s1, cmp_str_node);
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

	n = list_remove_val(lst, s2, cmp_str_node);
	assert(a == n && 0 == strcmp("Bee", (char*)n->val));
	free_node(n);

	free(list_free(lst, free_node));
}

void
test_remove_next() {
	list *lst = list_new(malloc(sizeof(list)));
	assert(lst);

	char *s1 = malloc(64*sizeof(char));
	strcpy(s1, "Apple");
	__attribute__((unused)) node *n1 = list_append(lst, s1, new_node);
	assert(n1);

	char *s2 = malloc(64*sizeof(char));
	strcpy(s2, "Bear");
	node *n2 = list_append(lst, s2, new_node);
	assert(n2);

	char *s3 = malloc(64*sizeof(char));
	strcpy(s3, "Code");
	node *n3 = list_append(lst, s3, new_node);
	assert(n3);
	assert(lst->tail == n3);

	node *removed = list_remove_next(lst, n3);
	assert(0 == removed);

	removed = list_remove_next(lst, n2);
	assert(removed);
	assert(list_tail(lst) == n2);
	free_node(removed);

	removed = list_remove_next(lst, lst->head);
	assert(removed);
	assert(removed == n2);
	free_node(removed);

	free(list_free(lst, free_node));
}

void
test_remove_tail() {
	list *lst = list_new(malloc(sizeof(list)));
	assert(lst);

	char *s1 = malloc(64*sizeof(char));
	strcpy(s1, "Apple");
	__attribute__((unused)) node *n1 = list_append(lst, s1, new_node);
	assert(n1);

	char *s2 = malloc(64*sizeof(char));
	strcpy(s2, "Bear");
	__attribute__((unused)) node *n2 = list_append(lst, s2, new_node);
	assert(n2);

	char *s3 = malloc(64*sizeof(char));
	strcpy(s3, "Code");
	__attribute__((unused)) node *n3 = list_append(lst, s3, new_node);
	assert(n3);
	assert(lst->tail == n3);

	node *tail = 0;
	while(!list_empty(lst)) {
		free_node(list_remove_tail(lst, &tail));
	}

	free(list_free(lst, free_node));
}

void
test_find()
{
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

	__attribute__((unused)) node *node = list_find(lst, i1, cmp_int_node);
	assert(node);

	list_free(lst, free_node);
	free(lst);
}

void
test_insert() {
	list* lst = list_new(malloc(sizeof(list)));
	assert(lst);

	node *n;

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
	assert(2 == list_size(lst));
	assert(lst->head != lst->tail);

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
main()
{
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
