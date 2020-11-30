#include <_algo_.h>

#if MSVC
#  pragma warning(disable : 4267)
#endif

void *
binary_search(const void *what, void *base, size_t nel, size_t width,
              int (*comp)(const void*lhs, const void *rhs))
{
  if (nel < 1) return NULL;

  long mid = nel/2;
  long c = comp(what, (char*)base + mid * width);
  if (0 == c)
    {
      return (char*)base + mid * width;
    }
  if (c < 0)
    {
      return binary_search(what,
                           base,
                           (size_t)(mid - 1 + 1),
                           width,
                           comp);
    }
  return binary_search(what,
                       (char*)base + (mid + 1) * width,
                       nel - mid - 1,
                       width,
                       comp);
}

void *
binary_search_loop(const void *what, void *base, size_t nel, size_t width,
                   int (*comp)(const void *lhs, const void *rhs))
{
  if (nel < 1) return NULL;

  long l = 0, r = nel-1;
  while (l <= r)
    {
      long mid = l + (r-l+1)/2;
      long c = comp(what, (char*) base + mid*width);
      if (0 == c)
        {
          return (char*) base + mid*width;
        }
      if (c < 0)
        {
          r = mid-1;
        } else
        {
          l = mid+1;
        }
    }
  return 0;
}

void
test_binary_search_int(void)
{
  int *found;
  int a1[] = {0x1, 0x2, 0x3, 0x4, 0x5 };
  int what = 0x5;
  printf("binary search for %i\n----------\n", what);
  list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = binary_search(&what,
                        a1,
                        sizeof(a1)/sizeof(*a1),
                        sizeof(*a1),
                        comp_int);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - a1));

  what = 0x6;
  printf("binary search for %i\n----------\n", what);
  list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = binary_search(&what,
                        a1,
                        sizeof(a1)/sizeof(*a1),
                        sizeof(*a1),
                        comp_int);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - a1));

  what = 0x3;
  printf("binary search for %i\n----------\n", what);
  list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = binary_search(&what,
                        a1,
                        sizeof(a1)/sizeof(*a1),
                        sizeof(*a1),
                        comp_int);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - a1));
}

void
test_binary_search_str(void)
{
  char **found;
  char *s1[] = { "a", "bb", "ccc", "dddd", "eeeee" };
  char *what = "dddd";
  printf("binary search for %s\n----------\n", what);
  list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = binary_search(&what,
                        s1,
                        sizeof(s1)/sizeof(*s1),
                        sizeof(*s1),
                        comp_str);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : (char**)found - s1));

  what = "ffffff";
  printf("binary search for %s\n----------\n", what);
  list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = binary_search(&what,
                        s1,
                        sizeof(s1)/sizeof(*s1),
                        sizeof(*s1),
                        comp_str);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - s1));

  what = "ccc";
  printf("binary search for %s\n----------\n", what);
  list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = binary_search(&what,
                        s1,
                        sizeof(s1)/sizeof(*s1),
                        sizeof(*s1),
                        comp_str);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - s1));
}

void
test_binary_search_loop_int(void)
{
  int *found;
  int a1[] = { 0x1, 0x2, 0x3, 0x4, 0x5 };
  int what = 0x5;
  printf("binary search loop for %i\n----------\n", what);
  list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = binary_search_loop(&what, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1),
                             comp_int);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - a1));

  what = 0x6;
  printf("binary search loop for %i\n----------\n", what);
  list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = binary_search_loop(&what,
                             a1,
                             sizeof(a1)/sizeof(*a1),
                             sizeof(*a1),
                             comp_int);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - a1));

  what = 0x3;
  printf("binary search loop for %i\n----------\n", what);
  list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = binary_search_loop(&what,
                             a1,
                             sizeof(a1)/sizeof(*a1),
                             sizeof(*a1),
                             comp_int);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - a1));
}

void
test_binary_search_loop_str(void)
{
  char **found;
  char *s1[] = { "a", "bb", "ccc", "dddd", "eeeee" };
  char *what = "dddd";
  printf("binary search loop for %s\n----------\n", what);
  list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = binary_search_loop(&what, s1, sizeof(s1)/sizeof(*s1), sizeof(*s1),
                             comp_str);
  printf("found: [%ld]\n", (long)(0 == found ? -1 : found - s1));

  what = "ffffff";
  printf("binary search loop for %s\n----------\n", what);
  list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = binary_search_loop(&what,
                             s1,
                             sizeof(s1)/sizeof(*s1),
                             sizeof(*s1),
                             comp_str);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - s1));

  what = "ccc";
  printf("binary search loop for %s\n----------\n", what);
  list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = binary_search_loop(&what,
                             s1,
                             sizeof(s1)/sizeof(*s1),
                             sizeof(*s1),
                             comp_str);
  printf("found: [%ld]\n", (long)(NULL == found ? -1 : found - s1));
}

int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  test_binary_search_int();
  test_binary_search_str();
  test_binary_search_loop_int();
  test_binary_search_loop_str();

  return 0;
}
