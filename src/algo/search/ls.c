#include <_algo_.h>

long linear_search(void*, void*, size_t, size_t,
                   int(*)(const void*, const void*));
void test_linear_search_int(void);
void test_linear_search_str(void);

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

  test_linear_search_int();
  test_linear_search_str();

	return 0;
}



long
linear_search(void *what, void *base, size_t nel, size_t width,
							int (*cmp)(const void *, const void *))
{
  for (size_t i = 0; i < nel; i++)
    {
      if (0 == cmp((char*)what, (char*)base + i * width))
        {
          return (long)i;
        }
    }
  return -1;
}

void
test_linear_search_int(void)
{
	int found;
	int a1[] = { 0x3, 0x5, 0x4, 0x1, 0x2 };
	int what = 0x1;
  const char *xx[] = { "ok", "failed" };
  int xxi = 1;

	printf("linear search for %i\n----------\n", what);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = linear_search(&what, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1),
                        cmp_int);
  if (found >= 0)
    {
      if (0 == verify(&what, &a1[found], sizeof(*a1)))
        {
          xxi = 0;
        }
    }
	printf("found: [%i] ... %s\n", found, xx[xxi]);

  what = 0x6;
	printf("linear search for %i\n----------\n", what);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
  found = linear_search(&what, a1, sizeof(a1)/sizeof(*a1), sizeof(*a1),
                        cmp_int);
  xxi = 1;
  if (found >= 0)
    {
      if (0 == verify(&what, &a1[found], sizeof(*a1)))
        {
          xxi = 0;
        }
    }

	printf("found: [%i] ... %s\n", found, xx[xxi]);
}

void
test_linear_search_str(void)
{
  int found;
	char *s1[] = { "a", "ccc", "bb", "dddd" };
	char *what = "dddd";
  const char *xx[] = { "ok", "failed" };
  int xxi = 1;

	printf("linear search for %s\n----------\n", what);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = linear_search(&what, s1, sizeof(s1)/sizeof(*s1), sizeof(*s1),
                        cmp_str);

  if (found >= 0)
    {
      if (0 == verify(&what, &s1[found], strlen(what)))
        {
          xxi = 0;
        }
    }
	printf("found: [%i] ... %s\n", found, xx[xxi]);

  what = "eeeee";
	printf("linear search for %s\n----------\n", what);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
  found = linear_search(&what, s1, sizeof(s1)/sizeof(*s1), sizeof(*s1),
                        cmp_str);

  xxi = 1;
  if (found >= 0)
    {
      if (0 == verify(&what, &s1[found], strlen(what)))
        {
          xxi = 0;
        }
    }
	printf("found: [%i] ... %s\n", found, xx[xxi]);
}
