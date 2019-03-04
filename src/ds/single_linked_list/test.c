#include "_ds_.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>

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
	node_s *n = calloc(1, sizeof(*n));
	assert(n && strerror(errno));
	
	n->val = val;
	return n;
}

int
cmp_str_node(const void *s1, const void *s2) {
  if (s1 && s2) {
    return strcmp(s1, s2);
  }
  return (int)((const char*)s1 - (const char*)s2);
}

int
cmp_int_node(const void *i1, const void *i2) {
  if (i1 && i2) {
    return *(int*)i1 - *(int*)i2;
  }

  return (int)((const int*)i1 - (const int*)i2);
}

void
iter_str_node(const node_s *node) {
  if (0 == node) {
    printf("0\n");
  } else {
    printf("[%p|%s]->", node, (char*)node->val);
  }
}

void
test_static_str_list() {
  node_s *head = list_append(0, "Apple", new_node);
  assert((0 != head) && (0 == strcmp(head->val, "Apple")));

	list_append(head, "Bee", new_node);
  list_append(head, "Candy", new_node);
  list_append(head, "Duck", new_node);

  node_s *nil = list_find(0, "Bee", cmp_str_node);
  assert(0 == nil);

  node_s *tail = list_find(head, 0, cmp_str_node);
  assert(0 == tail);
  
  node_s *bee = list_find(head, "Bee", cmp_str_node);
  assert(0 == strcmp(bee->val, "Bee"));
  list_iterate(head, iter_str_node);

  list_delete(&head, "Bee", cmp_str_node, free_node);
  assert(0 == list_find(head, "Bee", cmp_str_node));
  assert(0 != list_find(head, "Apple", cmp_str_node));
  list_iterate(head, iter_str_node);

  list_delete(&head, "Apple", cmp_str_node, free_node);
  assert(0 == strcmp("Candy", head->val));
  list_iterate(head, iter_str_node);
  
  list_free(head, free_node);
}

void
test_dynamic_str_list() {
  char *apple = malloc(32);
  node_s *head = list_append(0, strcpy(apple, "Apple"), new_node);
  assert((0 != head) && (0 == strcmp(apple, head->val)));

  char *bee = malloc(32);
  list_append(head, strcpy(bee, "Bee"), new_node);

  char *candy = malloc(32);
  list_append(head, strcpy(candy, "Candy"), new_node);

  char *duck = malloc(32);
  list_append(head, strcpy(duck, "Duck"), new_node);

  node_s *nil = list_find(0, bee, cmp_str_node);
  assert(0 == nil);

  node_s *tail = list_find(head, 0, cmp_str_node);
  assert(0 == tail);
  
  node_s *bee_node = list_find(head, bee, cmp_str_node);
  assert(0 == strcmp(bee_node->val, bee));

  list_delete(&head, bee, cmp_str_node, free_alloc_node);
  assert(0 == list_find(head, "Bee", cmp_str_node));
  assert(0 != list_find(head, apple, cmp_str_node));

  list_delete(&head, apple, cmp_str_node, free_alloc_node);
  assert(0 == strcmp(candy, head->val));

  list_free(head, free_alloc_node);
}

void
test_int_list() {
  int *one = malloc(sizeof(int));
  *one = 1;
  node_s *head = list_append(0, one, new_node);
  assert((0 != head) && (1 == *(int*)(head->val)));

  int *two = malloc(sizeof(int));
  *two = 2;
  list_append(head, two, new_node);

  int *three = malloc(sizeof(int));
  *three = 3;
  list_append(head, three, new_node);

  node_s *two_node = list_find(head, two, cmp_int_node);
  assert((0 != two_node) && (2 == *(int*)(two_node->val)));

  list_delete(&head, one, cmp_int_node, free_alloc_node);
  assert(2 == *(int*)(head->val));

  list_free(head, free_alloc_node);
}

int
main(void) {
	test_static_str_list();
  test_dynamic_str_list();
  test_int_list();

	return 0;
}
