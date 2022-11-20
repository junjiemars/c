#include "_ds_.h"
#include <stdio.h>
#include "list.h"

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
  while (h)
    {
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
  while (h)
    {
      printf("%8s %16s  at %p\n", "", *(char**) h->data, h->data);
      h = h->next;
    }
  putchar('\n');
}

void
test_list_new_free_int(void)
{
  list_s *s = list_new(0, sizeof(int));
  list_free(s);
}

void
test_list_int(void)
{
  int ss = 4;
  list_s *s = list_new(0, sizeof(int));
  node_s *n;
  int f = 5;
  int *pd = 0;

  printf("lists[int]: append/find/remove/prepend\n");
  printf("---------------------\n");


  for (int i = 1; i <= ss; i++)
    {
      n = list_append(s, &i);
      if (!n)
        {
          fprintf(stderr, "append wrong\n");
          goto clean_exit;
        }
      printf("%8s %16i  at %p\n", "append", *(int*) n->data, (int*) n->data);
    }
  putchar('\n');

  n = list_find(s, &f, cmp_int);
  if (!n)
    {
      printf("%8s %16i  no found\n", "find", f);
    }
  else
    {
      printf("%8s %16i  at %p\n", "find", *(int*)n->data, n->data);
    }

  f = 4;
  n = list_find(s, &f, cmp_int);
  if (!n)
    {
      printf("%8s %16i  no found\n", "find", f);
    }
  else
    {
      printf("%8s %16i  at %p\n", "find", *(int*)n->data, (int*) n->data);
    }

  f = *(int*) n->data;
  pd = (int*) n->data;
  list_remove(s, n);
  printf("%8s %16i  at %p\n", "remove", f, pd);

  f = 5;
  n = list_prepend(s, &f);
  if (n)
    {
      printf("%8s %16i  at %p\n", "prepend", *(int*)n->data, n->data);
    }
  else
    {
      printf("%8s %16i  wrong\n", "prepend", f);
    }
  print_list_int(s);

 clean_exit:
  list_free(s);
}

void
test_list_new_free_str(void)
{
  list_s *s = list_new(0, sizeof(char*));
  list_free(s);
}


void
test_list_str(void)
{
  char *ss[] = { "a", "bb", "ccc", "dddd", "eeeee", 0, };
  list_s *s = list_new(0, sizeof(char*));
  char **p = ss;
  node_s *n;
  char *f = "fffffff";
  char **pd = 0;

  printf("lists[str]: append/find/remove/prepend\n");
  printf("---------------------\n");

  while (*p)
    {
      n = list_append(s, p++);
      if (!n)
        {
          fprintf(stderr, "append wrong\n");
          goto clean_exit;
        }
      printf("%8s %16s  at %p\n", "append", *(char**) n->data, n->data);
    }
  putchar('\n');


  n = list_find(s, &f, cmp_str);
  if (n)
    {
      printf("%8s %16s  at %p\n", "find", *(char**) n->data, n->data);
    }
  else
    {
      printf("%8s %16s  no found\n", "find", f);
    }

  f = "dddd";
  n = list_find(s, &f, cmp_str);
  if (n)
    {
      printf("%8s %16s  at %p\n", "find", *(char**) n->data, n->data);
    }
  else
    {
      printf("%8s %16s  no found\n", "found", f);
    }

  f = *(char**) n->data;
  pd = (char**) n->data;
  list_remove(s, n);
  printf("%8s %16s  at %p\n", "remove", f, pd);

  f = "fffffff";
  n = list_prepend(s, &f);
  if (n)
    {
      printf("%8s %16s  at %p\n", "prepend", *(char**) n->data, n->data);
    }
  else
    {
      fprintf(stderr, "prepend wrong\n");
    }
  print_list_str(s);

 clean_exit:
  list_free(s);
}


int
main(void)
{
  test_list_new_free_int();
  test_list_int();

  test_list_new_free_str();
  test_list_str();

  return 0;
}
