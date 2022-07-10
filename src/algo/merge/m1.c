#include <_algo_.h>

/*
 * merge two arrays based on order
 */

static void merge(void*, size_t, void*, size_t, void*, size_t, size_t,
                  int(*)(const void*, const void*));
static void test_merge_int(void);
static void test_merge_str(void);

int
main(void)
{
  test_merge_int();
  test_merge_str();

	return 0;
}


void
merge(void * const l, size_t lnel,
      void * const r, size_t rnel,
      void * const m, size_t midx,
      size_t width,
      int (*cmp)(const void*lhs, const void *rhs))
{
  if (NULL == l && NULL == r)
    {
      return;
    }
  else if (0 == lnel)
    {
      memcpy((char*)m + midx * width, r, width * rnel);
      merge(0, 0, 0, 0, m, midx + rnel, width, cmp);
    }
  else if (0 == rnel)
    {
      memcpy((char*)m + midx * width, l, width * lnel);
      merge(0, 0, 0, 0, m, midx + lnel, width, cmp);
    }
  else if (cmp(l, r) <= 0)
    {
      memcpy((char*)m + midx * width, l, width);
      merge((char*)l + width, lnel-1, r, rnel, m, midx+1, width, cmp);
    }
  else
    {
      memcpy((char*)m + midx * width, r, width);
      merge(l, lnel, (char*)r + width, rnel-1, m, midx+1, width, cmp);
    }
}

void
test_merge_int(void)
{
  int al[] = {21, 28, 35, 40, 61, 75};
  int ar[] = {16, 25, 47, 54 };
  int am[sizeof(al)/sizeof(*al) + sizeof(ar)/sizeof(*ar)];
  size_t alnel = sizeof(al)/sizeof(*al);
  size_t arnel = sizeof(ar)/sizeof(*ar);
  size_t amnel = sizeof(am)/sizeof(*am);

  printf("merge int array ...\n----------\n");
  list_array(al, alnel, sizeof(*al), print_int);
  list_array(ar, arnel, sizeof(*ar), print_int);
  printf("----------\n");

  merge(al, alnel, ar, arnel, am, 0, sizeof(int), cmp_int);

  list_array(am, amnel, sizeof(*am), print_int);
}

void
test_merge_str(void)
{
  char *al[] = {"bb", "dddd", "eeeee", "ff", "i", "j"};
  char *ar[] = {"a", "ccc", "gg", "hhh" };
  char *am[sizeof(al)/sizeof(*al) + sizeof(ar)/sizeof(*ar)];
  size_t alnel = sizeof(al)/sizeof(*al);
  size_t arnel = sizeof(ar)/sizeof(*ar);
  size_t amnel = sizeof(am)/sizeof(*am);

  printf("merge str array ...\n----------\n");
  list_array(al, alnel, sizeof(*al), print_str);
  list_array(ar, arnel, sizeof(*ar), print_str);
  printf("----------\n");

  merge(al, alnel, ar, arnel, am, 0, sizeof(char*), cmp_str);

  list_array(am, amnel, sizeof(*am), print_str);
}
