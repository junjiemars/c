#include "_ds_.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


static void print_queue(queue_s *const q);

static void free_int_ptr(void *ptr);

static void test_queue_new_free_int(void);
static void test_queue_new_free_str(void);

static void test_queue_enq_deq_int(queue_s *const q);
static void test_queue_enq_deq_str(queue_s *const q);

static void test_queue_realloc(queue_s *const q);

void
print_queue(queue_s *const q)
{
  printf("---------------------\n");
  printf("%8s: %2i, %8s: %2i, %8s: %2zu, %8s: %2zu\n%8s= %p\n%8s= %p\n%8s= %2zu\n",
         "full", queue_full(q),
         "empty", queue_empty(q),
         "capacity", q->n,
         "size", queue_size(q),
         "head", q->head,
         "tail", q->tail,
         "offset", (char *) q->tail - (char *) q->head);
}


void
free_int_ptr(void *ptr)
{
  free(*(int **) ptr);
}


void
test_queue_new_free_int(void)
{
  queue_s    q;
  int        i;
  int       *one;
  int      **ints;
  int        ints_len;

  assert(NULL == queue_new(NULL, 4, sizeof(int), NULL));

  ints_len = 3;
  ints = malloc(sizeof(int*) * ints_len);
  assert(ints);
  
  queue_new(&q, 4, sizeof(int*), free_int_ptr);

  for (i = 0; i < ints_len; i++)
    {
      ints[i] = malloc(sizeof(int));
      *ints[i] = 2 * i;
      queue_enq(&q, &ints[i]);
    }
  for (i = 0; i < ints_len / 2; i++)
    {
      one = NULL;
      queue_deq(&q, &one);
      free_int_ptr(&one);
    }
  queue_free(&q);

  free(ints);
}


void
test_queue_enq_deq_int(queue_s *const q)
{
  int  *one;
  int   n, i, k;

  queue_new(q, 4, sizeof(int), NULL);
  n = (int) (q->n + 3);
  printf("queue int enq/deq [%zu/%i]\n", q->n, n);
  printf("---------------------\n");

  i = 0;
  while (i++ < n)
    {
      one = queue_enq(q, &i);
      if (0 == one)
        {
          fprintf(stderr, "enq failed\n");
          break;
        }
      printf("%8s %16i\n", "enq", *one);
    }

  printf("---------------------\n");
  k = 0;
  if (0 == queue_peek(q, &k))
    {
      fprintf(stderr, "peek failed, empty\n");
    }
  printf("%8s %16i\n", "peek", k);

  printf("---------------------\n");
  i = 0;
  while (i++ < 2 * n)
    {
      k = 0;
      one = queue_deq(q, &k);
      if (!one)
        {
          fprintf(stderr, "deq failed, empty\n");
          break;
        }
      printf("%8s %16i\n", "deq", k);
    }

  queue_free(q);
}

void
test_queue_new_free_str(void)
{
  queue_s  *q1;
  queue_s   q2;

  q1 = queue_new(NULL, 4, sizeof(char*), NULL);
  queue_free(q1);
  
  queue_new(&q2, 4, sizeof(char*), NULL);
  queue_free(&q2);
}

void
test_queue_enq_deq_str(queue_s *const q)
{
  size_t   i;
  char    *buf   =  0;
  char    *ss[]  =  {"a", "bb", "ccc", "dddd", "eeeee", "ffffff", };

  queue_new(q, 4, sizeof(char *), NULL);
  printf("queue str enq/deq [%zu/%zu]\n", q->n, sizeof(ss)/sizeof(*ss));
  printf("---------------------\n");
  
  for (i = 0; i < sizeof(ss)/sizeof(*ss); i++)
    {
      if (NULL == queue_enq(q, &ss[i]))
        {
          fprintf(stderr, "enq failed\n");
          break;
        }
      printf("%8s %16s\n", "enq", ss[i]);
    }

  printf("---------------------\n");
  if (NULL == queue_peek(q, &buf))
    {
      fprintf(stderr, "peek failed\n");
    }
  printf("%8s %16s\n", "peek", buf);

  printf("---------------------\n");
  for (i = 0; i < sizeof(ss)/sizeof(*ss); i++)
    {
      buf = 0;
      if (NULL == queue_deq(q, &buf))
        {
          fprintf(stderr, "deq failed, empty\n");
          break;
        }
      printf("%8s %16s\n", "deq", buf);
    }

  queue_free(q);
}


void
test_queue_realloc(queue_s *const q)
{
  int  n, i, k;

  queue_new(q, 4, sizeof(int), NULL);
  n = (int) q->n;
  printf("queue int enq/deq [%zu/%i]\n", q->n, n);
  printf("---------------------\n");

  i = 0;
  while (i++ < n)
    {
      k = 0;
      if (NULL == queue_enq(q, &k))
        {
          fprintf(stderr, "enq failed\n");
          break;
        }
      printf("%8s %16i\n", "enq", k);
    }
  print_queue(q);

  printf("---------------------\n");
  i = 0;
  while (i++ < n/2)
    {
      k = 0;
      queue_deq(q, &k);
      printf("%8s %16i\n", "deq", k);
    }
  print_queue(q);

  printf("---------------------\n");
  i = 0;
  while (i++ < 2)
    {
      k = 0;
      queue_enq(q, &k);
      printf("%8s %16i\n", "enq", k);
    }
  print_queue(q);

  printf("---------------------\n");
  i = 0;
  while (i++ < 2)
    {
      k = 0;
      queue_enq(q, &k);
      printf("%8s %16i\n", "enq", k);
    }
  print_queue(q);

  printf("---------------------\n");
  queue_deq(q, &k);
  printf("%8s %16i\n", "deq", k);
  print_queue(q);

  printf("---------------------\n");
  i = 0;
  while (i++ < 1)
    {
      k = 0;
      queue_enq(q, &k);
      printf("%8s %16i\n", "enq", k);
    }
  print_queue(q);

  printf("---------------------\n");
  i = 0;
  while (i++ < n+3)
    {
      k = 0;
      queue_enq(q, &k);
      printf("%8s %16i\n", "enq", k);
    }
  print_queue(q);
  
  queue_free(q);
}


int
main(void)
{
  queue_s  q;

  test_queue_new_free_int();
  test_queue_new_free_str();

  test_queue_enq_deq_int(&q);
  test_queue_enq_deq_str(&q);

  test_queue_realloc(&q);
  
  return 0;
}
