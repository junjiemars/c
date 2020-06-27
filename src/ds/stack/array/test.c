#include "_ds_.h"
#include "stack.h"
#include <stdio.h>


void
test_stack_new_free_int(void) {
  stack_s *s = stack_new(0, 4, sizeof(int));
  stack_free(s);
}

void
test_stack_push_pop_int(void) {
  stack_s *s = stack_new(0, 4, sizeof(int));
  int n = s->n + 3, i = 0;

  printf("stack int push/pop [%zu/%i]\n", s->n, n);
  printf("---------------------\n");

  while (i++ < n) {
    stack_push(s, &i);
    printf("%8s %16i\n", "push", i);
  }

  printf("---------------------\n");
  i = 0;
  while (i++ < 2*n) {
    int k = 0;
    int empty = stack_pop(s, &k);
    if (0 == empty) {
      break;
    }
    printf("%8s %16i\n", "pop", k);
  }

  stack_free(s);
}

void
test_stack_new_free_str() {
  stack_s *s = stack_new(0, 4, sizeof(char*));
  stack_free(s);
}

void
test_stack_push_pop_str(void) {
  stack_s *s = stack_new(0, 4, sizeof(char*));
  char *ss[] = {"a", "bb", "ccc", "dddd", "eeeee", "ffffff", };

  printf("stack str push/pop [%zu/%zu]\n", s->n, sizeof(ss)/sizeof(ss[0]));
  printf("---------------------\n");
  
  for (size_t i = 0; i < sizeof(ss)/sizeof(ss[0]); i++) {
    stack_push(s, &ss[i]);
    printf("%8s %16s\n", "push", ss[i]);
  }

  printf("---------------------\n");
  for (size_t i = 0; i < sizeof(ss)/sizeof(ss[0]); i++) {
    char *buf = 0;
    int empty = stack_pop(s, &buf);
    if (0 == empty) {
      break;
    }
    printf("%8s %16s\n", "pop", buf);
  }

  stack_free(s);
}


int
main(void) {
  test_stack_new_free_int();
  test_stack_push_pop_int();
  
  test_stack_new_free_str();
  test_stack_push_pop_str();
  
  return 0;
}
