#include "_ds_.h"
#include "stack.h"
#include <stdio.h>

#if (MSVC)
#  pragma warning(disable:4267) /* conversion from 'size_t' to 'int' */
#endif


static void test_stack_new_free_int(void);
static void test_stack_push_pop_int(stack_s *s);

static void test_stack_push_pop_int(stack_s *s);
static void test_stack_push_pop_str(stack_s *s);

static void test_stack_push_pop_ptr(stack_s *s);

void
test_stack_new_free_int(void)
{
  stack_s   s1;
  stack_s  *s2;

  s2 = stack_new(NULL, 4, sizeof(int), NULL);
  stack_free(s2);

  stack_new(&s1, 4, sizeof(int), NULL);
  stack_free(&s1);
}

void
test_stack_push_pop_int(stack_s *s)
{
  int         n;
  int         i;

  stack_new(s, 4, sizeof(int), NULL);
  n = s->n + 3;
  i = 0;

  printf("stack int push/pop [%i/%zu]\n", n, s->n);
  printf("---------------------\n");

  while (i++ < n)
    {
      int *one = stack_push(s, &i);
      if (0 == one)
        {
          fprintf(stderr, "push failed\n");
          break;
        }
      printf("%8s %16i\n", "push", i);
    }

  printf("---------------------\n");
  if (0 == stack_peek(s, &i))
    {
      fprintf(stderr, "peek failed\n");
    }
  printf("%8s %16i\n", "peek", i);

  printf("---------------------\n");
  i = 0;
  while (i++ < 2*n) {
    int k = 0;
    int *empty = stack_pop(s, &k);
    if (0 == empty)
      {
        fprintf(stderr, "pop failed, empty\n");
        break;
      }
    printf("%8s %16i\n", "pop", k);
  }

  stack_free(s);
}

void
test_stack_new_free_str()
{
  stack_s s1;
  stack_s *s2;

  s2 = stack_new(NULL, 4, sizeof(char*), NULL);
  stack_free(s2);
  
  stack_new(&s1, 4, sizeof(char*), NULL);
  stack_free(&s1);
}

void
test_stack_push_pop_str(stack_s *s)
{
  char *ss[] = {"a", "bb", "ccc", "dddd", "eeeee", "ffffff", };
  char *buf = 0;

  stack_new(s, 4, sizeof(char*), NULL);
  printf("stack str push/pop [%zu/%zu]\n", sizeof(ss)/sizeof(ss[0]), s->n);
  printf("---------------------\n");
  
  for (size_t i = 0; i < sizeof(ss)/sizeof(ss[0]); i++)
    {
      char *one = stack_push(s, &ss[i]);
      if (0 == one)
        {
          fprintf(stderr, "push failed\n");
          break;
        }
      printf("%8s %16s\n", "push", ss[i]);
    }

  printf("---------------------\n");
  if (0 == stack_peek(s, &buf))
    {
      fprintf(stderr, "peek failed\n");
    }
  printf("%8s %16s\n", "peek", buf);

  printf("---------------------\n");
  for (size_t i = 0; i < sizeof(ss)/sizeof(ss[0]); i++)
    {
      buf = 0;
      char *empty = stack_pop(s, &buf);
      if (0 == empty)
        {
          fprintf(stderr, "pop failed, empty\n");
          break;
        }
      printf("%8s %16s\n", "pop", buf);
    }

  stack_free(s);
}


void
test_stack_push_pop_ptr(stack_s *s)
{
  int   n;
  int   i;
  int  *k;
  int  *one;

  stack_new(s, 8, sizeof(int*), free);
  n = s->n - 3;
  i = 0;
  k = 0;

  printf("stack int* push/pop [%i/%zu]\n", n, s->n);
  printf("---------------------\n");

  while (i++ < n)
    {
      one = malloc(sizeof(int));
      *one = i;

      if (NULL == stack_push(s, &one))
        {
          fprintf(stderr, "push failed\n");
          break;
        }
      printf("%8s %16i\n", "push", i);
    }

  printf("---------------------\n");
  if (NULL == stack_peek(s, &k))
    {
      fprintf(stderr, "peek failed\n");
    }
  printf("%8s %16i\n", "peek", *k);

  printf("---------------------\n");
  i = 0;
  while (i++ < 2*n)
    {
      if (NULL == stack_pop(s, &k))
        {
          fprintf(stderr, "pop failed, empty\n");
          break;
        }
      printf("%8s %16i\n", "pop", *k);
    }

  stack_free(s);
}

int
main(void)
{
  stack_s   ss;

  test_stack_new_free_int();
  test_stack_new_free_str();

  test_stack_push_pop_int(&ss);
  test_stack_push_pop_str(&ss);

  test_stack_push_pop_ptr(&ss);

  return 0;
}
