#include "_ds_.h"
#include "list.h"
#include <stdio.h>

int
cmp_int(const void *a, const void *b) {
  int x = *(const int*)a - *(const int*)b;
  return x;
}

void
print_list_int(list_s *const s) {
  node_s *h = s->head;
  while (h) {
    printf("%16i  at %p\n", *(int*)h->data, h->data);
    h = h->next;
  }
  putchar('\n');
}

void
test_list_new_free_int(void) {
  list_s *s = list_new(0, sizeof(int));
  list_free(s);
}

void
test_list_int(void) {
  int ss = 4;
  list_s *s = list_new(0, sizeof(int));

  printf("list int append/find/remove/delete\n");
  printf("---------------------\n");  

  node_s *n;
  for (int i = 1; i <= ss; i++) {
    n = list_append(s, &i);
    if (!n) {
      fprintf(stderr, "append failed\n");
      goto clean_exit;
    }
    printf("%8s %16i  at %p\n", "append", *(int*)n->data, n->data);
  }
  putchar('\n');

  int f = 5;
  printf("find '%i', ", f);
  n = list_find(s, &f, cmp_int);
  if (!n) {
    printf("no found\n");
  } else {
    printf("found '%i' at %p\n", *(int*)n->data, n->data);
  }

  f = 4;
  printf("find '%i', ", f);
  n = list_find(s, &f, cmp_int);
  if (!n) {
    printf("no found\n");
  } else {
    printf("found '%i' at %p\n", *(int*)n->data, n->data);
  }

  printf("remove '%i' at %p\n", *(int*)n->data, n->data);
  list_remove(s, n);
  print_list_int(s);

 clean_exit:
  list_free(s);
}


int
cmp_str(const void *a, const void*b) {
  int c = strcmp(*(char const**)&a, *(char const**)&b);
  return c;
}

void
print_list_str(list_s *const s) {
  node_s *h = s->head;
  while (h) {
    printf("%16s  at %p\n", *(char**)h->data, h->data);
    h = h->next;
  }
  putchar('\n');
}

void
test_list_new_free_str(void) {
  list_s *s = list_new(0, sizeof(char*));
  list_free(s);
}

void
test_list_str(void) {
  char *ss[] = { "a", "bb", "ccc", "dddd", "eeeee", 0, };

  list_s *s = list_new(0, sizeof(char*));

  printf("list str append/find/remove/delete\n");
  printf("---------------------\n");  
  
  char **p = ss;
  node_s *n;
  while (*p) {
    n = list_append(s, p++);
    if (!n) {
      fprintf(stderr, "append failed\n");
      goto clean_exit;
    }
    printf("%8s %16s  at %p\n", "append", *(char**)n->data, n->data);
  }
  putchar('\n');

  char *f = "fffffff";
  printf("find '%s', ", f);

  n = list_find(s, &f, cmp_str);
  if (!n) {
    printf("no found\n");
  } else {
    printf("found '%s' at %p\n", f, n->data);
  }

  f = "dddd";
  printf("str find '%s', ", f);
  n = list_find(s, &f, cmp_str);
  if (!n) {
    printf("no found '%s'\n", f);
  } else {
    printf("found '%s' at %p\n", f, n->data);
  }

  printf("remove '%s' at %p\n", *(char**)n->data, n->data);
  list_remove(s, n);
  print_list_str(s);

 clean_exit:
  list_free(s);
}

int
main(void) {
  test_list_new_free_int();
  test_list_int();

  test_list_new_free_str();
  test_list_str();

  return 0;
}
