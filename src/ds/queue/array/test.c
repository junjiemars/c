#include "_ds_.h"
#include "queue.h"
#include <stdio.h>


void
print_queue(queue_s *const s) {
  printf("---------------------\n");
  printf("%8s: %2i, top: %p, tail: %p\n", "full",
         queue_full(s), s->head, s->tail);
  printf("%8s: %2i, top: %p, tail: %p\n", "empty",
         queue_empty(s), s->head, s->tail);
  printf("%8s: %2zu, top: %p, tail: %p\n", "capacity",
         s->n, s->head, s->tail);
}

void
test_queue_new_free_int(void) {
  queue_s *s = queue_new(0, 4, sizeof(int));
  queue_free(s);
}

void
test_queue_realloc(void) {
  queue_s *s = queue_new(0, 4, sizeof(int));
  int n = s->n, i = 0, v = 0;

  printf("queue int enq/deq [%zu/%i]\n", s->n, n);
  printf("---------------------\n");

  while (i++ < n) {
    int *one = queue_enq(s, &i);
    if (0 == one) {
      fprintf(stderr, "enq failed\n");
      break;
    }
    printf("%8s %16i\n", "enq", i);
  }
  print_queue(s);

  printf("---------------------\n");
  i = 0;
  while (i++ < n) {
    queue_deq(s, &v);
    printf("%8s %16i\n", "enq", v);
  }

  printf("---------------------\n");
  v = 5;
  queue_enq(s, &v);
  print_queue(s);

  i = 0;
  while (i++ < n+2) {
    int *one = queue_enq(s, &i);
    if (0 == one) {
      fprintf(stderr, "enq failed\n");
      break;
    }
    printf("%8s %16i\n", "enq", i);
  }

  print_queue(s);

  queue_free(s);
}

void
test_queue_enq_deq_int(void) {
  queue_s *s = queue_new(0, 4, sizeof(int));
  int n = s->n + 3, i = 0;

  printf("queue int enq/deq [%zu/%i]\n", s->n, n);
  printf("---------------------\n");

  while (i++ < n) {
    int *one = queue_enq(s, &i);
    if (0 == one) {
      fprintf(stderr, "enq failed\n");
      break;
    }
    printf("%8s %16i\n", "enq", i);
  }

  printf("---------------------\n");
  if (0 == queue_peek(s, &i)) {
    fprintf(stderr, "peek failed, empty\n");
  }
  printf("%8s %16i\n", "peek", i);

  printf("---------------------\n");
  i = 0;
  while (i++ < 2*n) {
    int k = 0;
    int *empty = queue_deq(s, &k);
    if (0 == empty) {
      fprintf(stderr, "deq failed, empty\n");
      break;
    }
    printf("%8s %16i\n", "deq", k);
  }

  queue_free(s);
}

void
test_queue_new_free_str() {
  queue_s *s = queue_new(0, 4, sizeof(char*));
  queue_free(s);
}

void
test_queue_enq_deq_str(void) {
  queue_s *s = queue_new(0, 4, sizeof(char*));
  char *ss[] = {"a", "bb", "ccc", "dddd", "eeeee", "ffffff", };
  char *buf = 0;

  printf("queue str enq/deq [%zu/%zu]\n", s->n, sizeof(ss)/sizeof(ss[0]));
  printf("---------------------\n");
  
  for (size_t i = 0; i < sizeof(ss)/sizeof(ss[0]); i++) {
    char *one = queue_enq(s, &ss[i]);
    if (0 == one) {
      fprintf(stderr, "enq failed\n");
      break;
    }
    printf("%8s %16s\n", "enq", ss[i]);
  }

  printf("---------------------\n");
  if (0 == queue_peek(s, &buf)) {
    fprintf(stderr, "peek failed\n");
  }
  printf("%8s %16s\n", "peek", buf);

  printf("---------------------\n");
  for (size_t i = 0; i < sizeof(ss)/sizeof(ss[0]); i++) {
    buf = 0;
    char *empty = queue_deq(s, &buf);
    if (0 == empty) {
      fprintf(stderr, "deq failed, empty\n");
      break;
    }
    printf("%8s %16s\n", "deq", buf);
  }

  queue_free(s);
}


int
main(void) {
  test_queue_new_free_int();
  test_queue_enq_deq_int();
  test_queue_realloc();
  
  test_queue_new_free_str();
  test_queue_enq_deq_str();
  
  return 0;
}
