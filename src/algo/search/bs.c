#include <_algo_.h>

/*
 * bs and bs_iter implement the same functionality as the bsearch in
 * stdlib.h
 *
 * bs using tail-recursive, if CC supports tail-recursion optimization
 * and bs should as fast as bs_iter does.
 */


#if MSVC
#  pragma warning(disable : 4267)
#endif


void * bs(const void *key, const void *base, size_t n, size_t width,
          int (*cmp)(const void *lhs, const void *rhs));

void * bs_iter(const void *key, const void *base, size_t n, size_t width,
               int (*cmp)(const void *lhs, const void *rhs));

static void test_bs_int(const void *key, const void *base,
                        size_t n, size_t width);
static void test_bs_str(const void *key, const void *base,
                        size_t n, size_t width);

static void test_bs_iter_int(const void *key, const void *base,
                             size_t n, size_t width);
static void test_bs_iter_str(const void *key, const void *base,
                             size_t n, size_t width);

static void test_bsearch_int(const void *key, const void *base,
                             size_t n, size_t width);
static void test_bsearch_str(const void *key, const void *base,
                             size_t n, size_t width);

void *
bs(const void *key, const void *base, size_t n, size_t width,
   int (*cmp)(const void *lhs, const void *rhs))
{
  if (n < 1) {
    return NULL;
  }

  size_t mid = (size_t) (n/2);
  void *cur = (char*) base + mid * width;
  long c = cmp(key, cur);

  if (0 == c)
    {
      return cur;
    }

  if (c < 0)
    {
      return bs(key, base, mid - 1 + 1, width, cmp);
    }

  return bs(key, (char*) base + (mid + 1) * width,
            n - mid - 1,
            width,
            cmp);
}

void *
bs_iter(const void *key, const void *base, size_t n, size_t width,
        int (*cmp)(const void *lhs, const void *rhs))
{
  if (n < 1) {
    return NULL;
  }

  long l = 0, r = n - 1;
  while (l <= r)
    {
      long mid = l + (r - l + 1) / 2;
      void *cur = (char*) base + mid * width;
      long c = cmp(key, cur);
      if (0 == c)
        {
          return cur;
        }
      if (c < 0)
        {
          r = mid - 1;
        } else
        {
          l = mid + 1;
        }
    }
  return NULL;
}

void
test_bs_int(const void *key, const void *base,
            size_t n, size_t width)
{
  int *found;

  printf("binary search for %i\n----------\n", *(int *) key);
  list_array(base, n, width, print_int);
  found = bs(key, base, n, width, cmp_int);
  printf("found: [%ld]\n",
         (NULL == found ? -1L : (long) offset(base, found, sizeof(*found))));
}

void
test_bs_str(const void *key, const void *base,
            size_t n, size_t width)
{
  char **found;
  /* char *s1[] = { "a", "bb", "ccc", "dddd", "eeeee" }; */
  /* char *what = "dddd"; */

  printf("binary search for %s\n----------\n", *(char**) key);
  list_array(base, n, width, print_str);
  found = bs(key, base, n, width, cmp_str);
  printf("found: [%ld]\n",
         (NULL == found ? -1L : (long) offset(base, found, width)));
}

void
test_bs_iter_int(const void *key, const void *base,
                 size_t n, size_t width)
{
  int *found;

  printf("binary search iter for %i\n----------\n", *(int*) key);
  list_array(base, n, width, print_int);
  found = bs_iter(key, base, n, width, cmp_int);
  printf("found: [%ld]\n",
         (NULL == found ? -1L : (long) offset(base, found, sizeof(*found))));
}

void
test_bs_iter_str(const void *key, const void *base,
                 size_t n, size_t width)
{
  char **found;
  
  printf("binary search iter for %s\n----------\n", *(char**) key);
  list_array(base, n, width, print_str);
  found = bs_iter(key, base, n, width, cmp_str);
  printf("found: [%ld]\n",
         (0 == found ? -1L : (long) offset(base, found, width)));
}

void
test_bsearch_int(const void *key, const void *base,
                 size_t n, size_t width)
{
  int *found;
  
  printf("bsearch for %i\n----------\n", *(int*) key);
  list_array(base, n, width, print_int);
  found = bsearch(key, base, n, width, cmp_int);
  printf("found: [%ld]\n",
         (NULL == found ? -1L : (long) offset(base, found, width)));
}

void
test_bsearch_str(const void *key, const void *base,
                 size_t n, size_t width)
{
  char **found;

  printf("bsearch for %s\n----------\n", *(char**) key);
  list_array(base, n, width, print_str);
  found = bs(key, base, n, width, cmp_str);
  printf("found: [%ld]\n",
         (NULL == found ? -1L : (long) offset(base, found, width)));
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  int int_base[] = { 0x1, 0x2, 0x3, 0x4, 0x5 };
  int int_keys[] = { 0x5, 0x6, 0x3 };
  char *str_base[] = { "a", "bb", "ccc", "dddd", "eeeee" };
  char *str_keys[] = { "dddd", "ffffff", "ccc" };

  /* bs */
  for (size_t i = 0; i < count(int_keys); i++) {
    test_bs_int(&int_keys[i],
                int_base,
                count(int_base),
                sizeof(*int_base));
  }
  for (size_t i = 0; i < count(str_keys); i++) {
    test_bs_str(&str_keys[i],
                str_base,
                count(str_base),
                sizeof(*str_base));
  }


  /* bs_iter */
  for (size_t i = 0; i < count(int_keys); i++) {
    test_bs_iter_int(&int_keys[i],
                     int_base,
                     count(int_base),
                     sizeof(*int_base));
  }
  for (size_t i = 0; i < count(str_keys); i++) {
    test_bs_iter_str(&str_keys[i],
                     str_base,
                     count(str_base),
                     sizeof(*str_base));
  }

  /* bsearch */
  for (size_t i = 0; i < count(int_keys); i++) {
    test_bsearch_int(&int_keys[i],
                     int_base,
                     count(int_base),
                     sizeof(*int_base));
  }
  for (size_t i = 0; i < count(str_keys); i++) {
    test_bsearch_str(&str_keys[i],
                     str_base,
                     count(str_base),
                     sizeof(*str_base));
  }
  return 0;
}
