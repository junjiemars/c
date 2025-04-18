#include <_algo_.h>
#include "algo_search.h"

void test_linear_search_int (void);
void test_linear_search_str (void);

static char const *xx[] = { "yes", "no" };

int
main (void)
{
  test_linear_search_int ();
  test_linear_search_str ();

  return 0;
}

void *
linear_search (void const *what, void const *base, size_t n, size_t width,
               int (*cmp) (void const *, void const *))
{
  char *ep, *endp;

  ep = (char *)base;
  for (endp = (char *)(ep + width * n); ep < endp; ep += width)
    {
      if (cmp (what, ep) == 0)
        {
          return ep;
        }
    }
  return NULL;
}

void
test_linear_search_int (void)
{
  int *found;
  int a1[] = { 0x3, 0x5, 0x4, 0x1, 0x2 };
  int what = 0x1;

  int xxi = 1;

  printf ("linear search for %i\n----------\n", what);
  list_array (a1, sizeof (a1) / sizeof (*a1), sizeof (*a1), print_int);
  found = linear_search (&what, a1, sizeof (a1) / sizeof (*a1), sizeof (*a1),
                         cmp_int);
  if (found)
    {
      if (0 == verify (&what, found, sizeof (*a1)))
        {
          xxi = 0;
        }
    }
  printf ("found: [%i] ... %s\n", what, xx[xxi]);

  what = 0x6;
  printf ("linear search for %i\n----------\n", what);
  list_array (a1, sizeof (a1) / sizeof (*a1), sizeof (*a1), print_int);
  found = linear_search (&what, a1, sizeof (a1) / sizeof (*a1), sizeof (*a1),
                         cmp_int);
  xxi = 1;
  if (found)
    {
      if (0 == verify (&what, found, sizeof (*a1)))
        {
          xxi = 0;
        }
    }
  printf ("found: [%i] ... %s\n", what, xx[xxi]);
}

void
test_linear_search_str (void)
{
  char **found;
  char *s1[] = { "a", "ccc", "bb", "dddd" };
  char *what = "dddd";
  int xxi = 1;

  printf ("linear search for %s\n----------\n", what);
  list_array (s1, sizeof (s1) / sizeof (*s1), sizeof (*s1), print_str);
  found = linear_search (&what, s1, sizeof (s1) / sizeof (*s1), sizeof (*s1),
                         cmp_str);

  if (found)
    {
      if (0 == verify (&what, found, strlen (what)))
        {
          xxi = 0;
        }
    }
  printf ("found: [%s] ... %s\n", what, xx[xxi]);

  what = "eeeee";
  printf ("linear search for %s\n----------\n", what);
  list_array (s1, sizeof (s1) / sizeof (*s1), sizeof (*s1), print_str);
  found = linear_search (&what, s1, sizeof (s1) / sizeof (*s1), sizeof (*s1),
                         cmp_str);

  xxi = 1;
  if (found)
    {
      if (0 == verify (&what, found, strlen (what)))
        {
          xxi = 0;
        }
    }
  printf ("found: [%s] ... %s\n", what, xx[xxi]);
}
