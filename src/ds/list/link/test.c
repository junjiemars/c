#include "_ds_.h"
#include "list.h"
#include <stdio.h>

void print_list_int(list_s *const s) {
  node_s *h = s->head;
  while (h) {
    printf("%i, ", *(int*)h->data);
    h = h->next;
  }
  putchar('\n');
}

int
cmp_int(const void *a, const void *b) {
  int x = *(const int*)a - *(const int*)b;
  return x;
}

void
test_list_new_free_int() {
  list_s *s = list_new(0, sizeof(int));
  list_free(s);
}

void
test_list_append_int() {
  list_s *s = list_new(0, sizeof(int));
  int n = 4;
  for (int i = 1; i <= n; i++) {
    node_s *c = list_append(s, &i);
    printf("%i, ", *(int*)c->data);
  }
  putchar('\n');

  list_free(s);
}

void
test_list_find_int() {
  list_s *s = list_new(0, sizeof(int));
  int n = 4, v;
  node_s *c;
  for (int i = 1; i <= n; i++) {
    c = list_append(s, &i);
    printf("%i, ", *(int*)c->data);
  }
  putchar('\n');

  v = 3;
  c = list_find(s, &v, cmp_int);
  if (c) {
    printf("%i\n", *(int*)c->data);
  }

  list_free(s);
}

void
test_list_remove_int() {
  list_s *s = list_new(0, sizeof(int));
  int n = 4, v;
  node_s *c;
  for (int i = 1; i <= n; i++) {
    c = list_append(s, &i);
    printf("%i, ", *(int*)c->data);
  }
  putchar('\n');

  v = 3;
  c = list_find(s, &v, cmp_int);
  if (c) {
    printf("%i\n", *(int*)c->data);
    if (list_remove(s, c)) {
      printf("remove it\n");
    }
  }

  list_free(s);
}

int
main(void) {
  test_list_new_free_int();
  test_list_append_int();
  test_list_find_int();
  test_list_remove_int();
  
  return 0;
}
