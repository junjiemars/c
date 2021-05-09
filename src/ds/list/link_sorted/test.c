#include "_ds_.h"
#include "list.h"
#include <stdio.h>

int cmp_int(const void *a, const void *b);
int cmp_str(const void *a, const void*b);

void print_list_int(list_s *const s);
void print_list_str(list_s *const s);
 
int
cmp_int(const void *a, const void *b)
{
  int x = *(const int*) a - *(const int*) b;
  return x;
}

void
print_list_int(list_s *const s)
{
  printf("---------------------\n");
  node_s *h = s->head;
  while (h) {
    printf("%16i  at %p\n", *(int*) h->data, h->data);
    h = h->next;
  }
  putchar('\n');
}

int
cmp_str(const void *a, const void*b)
{
  int c = strcmp(*(char* const*) a, *(char* const*) b);
  return c;
}

void
print_list_str(list_s *const s)
{
  printf("---------------------\n");
  node_s *h = s->head;
  while (h) {
    printf("%8s %16s  at %p\n", "", *(char**) h->data, h->data);
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
  int ss[] = { 3, 2, 5, 4, 1, };
  list_s *s = list_new(0, sizeof(int));

  printf("list[sort|int]: insert/find/remove\n");
  printf("---------------------\n");

  node_s *n;
  for (size_t i = 0; i < sizeof(ss)/sizeof(ss[0]); i++) {
    n = list_insert(s, &ss[i], cmp_int);
    if (!n) {
      fprintf(stderr, "insert failed\n");
      goto clean_exit;
    }
    printf("%8s %16i  at %p\n", "insert", *(int*)n->data, n->data);
  }
  putchar('\n');

  int f = -1;
  n = list_find(s, &f, cmp_int);
  if (!n) {
    printf("%8s %16i  no found\n", "find", f);
  } else {
    printf("%8s %16i  at %p\n", "find", *(int*)n->data, n->data);
  }

  f = 4;
  n = list_find(s, &f, cmp_int);
  if (!n) {
    printf("%8s %16i  no found\n", "find", f);
  } else {
    printf("%8s %16i  at %p\n", "find", *(int*)n->data, n->data);
  }

  f = *(int*)n->data;
  if (list_remove(s, n)) {
    printf("%8s %16i  at %p\n", "remove", f, &f);
  } else {
    printf("%8s %16i  failed\n", "remove", f);
  }

  f = 1;
  n = list_insert(s, &f, cmp_int);
  if (n) {
    printf("%8s %16i  at %p\n", "insert", *(int*)n->data, n->data);
  } else {
    printf("%8s %16i  failed\n", "insert", f);
  }
  
  print_list_int(s);  

 clean_exit:
  list_free(s);
}


void
test_list_new_free_str(void) {
  list_s *s = list_new(0, sizeof(char*));
  list_free(s);
}

void
test_list_str(void) {
  char *ss[] = { "ccc", "bb", "a", "dddd", "eeeee", 0, };
  list_s *s = list_new(0, sizeof(char*));

  printf("lists[sort|str]: insert/find/remove\n");
  printf("---------------------\n");
  
  char **p = ss;
  node_s *n;
  while (*p) {
    n = list_insert(s, p++, cmp_str);
    if (!n) {
      fprintf(stderr, "insert failed\n");
      goto clean_exit;
    }
    printf("%8s %16s  at %p\n", "insert", *(char**)n->data, n->data);
  }
  putchar('\n');

  char *f = "fffffff";
  n = list_find(s, &f, cmp_str);
  if (n) {
    printf("%8s %16s  at %p\n", "find", *(char**)n->data, n->data);
  } else {
    printf("%8s %16s  no found\n", "find", f);
  }

  f = "dddd";
  n = list_find(s, &f, cmp_str);
  if (n) {
    printf("%8s %16s  at %p\n", "find", *(char**)n->data, n->data);
  } else {
    printf("%8s %16s  no found\n", "found", f);
  }

  f = *(char**)n->data;
  if (list_remove(s, n)) {
    printf("%8s %16s  at %p\n", "remove", f, &f);
  } else {
    printf("%8s %16s failed\n", "remove", f);
  }

  f = "a";
  n = list_insert(s, &f, cmp_str);
  if (n) {
    printf("%8s %16s  at %p\n", "insert", *(char**)n->data, n->data);
  } else {
    printf("%8s %16s  failed\n", "insert", f);
  }

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
