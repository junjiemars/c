#include "_ds_.h"
#include "list.h"
#include <stdio.h>

void print_list_int(list_s *const s) {
  node_s *h = s->head;
  while (h) {
    printf("%i, ", *(int*)&h->data);
    h = h->next;
  }
  putchar('\n');
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

int
main(void) {
  test_list_new_free_int();
  test_list_append_int();

  return 0;
}
