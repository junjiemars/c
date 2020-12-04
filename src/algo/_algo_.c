#include "_algo_.h"
#include <string.h>

void
list_array(const void *base, size_t nel, size_t width,
					 void (*print)(const void *el))
{
	for (size_t i = 0; i < nel; i++)
    {
      print((char*) base + i * width);
    }
	printf("\n");
}

void
print_int(const void *el)
{
	printf("%i, ", *(int*) el);
}

void
print_str(const void *el)
{
	printf("%s, ", *(char**) el);
}

int
cmp_int(const void *lhs, const void *rhs)
{
	return *(const int*)lhs - *(const int*)rhs;
}

int
cmp_str(const void *lhs, const void *rhs)
{
	return strcmp(*(const char**)lhs, *(const char**)rhs);
}

int
verify(const void *lhs, const void *rhs, size_t size)
{
  return memcmp((const char*)lhs, (const char*)rhs, size);
}

#if _ALGO_TEST_

void
test_cmp_int(void)
{
	int i1 = 0x1122, i2 = 0x3344;
	int cmp = cmp_int(&i1, &i2);
  _unused_(cmp);
	assert(cmp < 0 && "cmp_int(0x1122, 0x3344) should < 0");
	cmp = cmp_int(&i1, &i1);
	assert(cmp == 0 && "cmp_int(0x1122, 0x1122) should == 0");
	cmp = cmp_int(&i2, &i1);
	assert(cmp > 0 && "cmp_int(0x3344, 0x1122) should > 0");
	printf("test cmp_int fn ... ok\n");
}

void
test_cmp_str(void)
{
	char *ss[] = { "abc123", "123", };
	assert(0 == cmp_str(ss, ss));
	assert(0 != cmp_str(&ss[0], &ss[1]));
	char *s1 = ss[0]+3;
  _unused_(s1);
	assert(0 == cmp_str(&s1, &ss[1]));
	printf("test cmp_str fn ... ok\n");
}

void
test_verify(void)
{
	char *ss[] = { "abc", "12345" };
  size_t s1 = strlen(ss[0]);
  size_t s2 = strlen(ss[1]);
  assert(0 == verify(&ss[0], &ss[0], MIN(s1, s1)));
  assert(0 != verify(&ss[0], &ss[1], MIN(s1, s2)));

  int ii[] = { 1234, 12345 };
  assert(0 == verify(&ii[0], &ii[0], sizeof(*ii)));
  assert(0 != verify(&ii[0], &ii[1], sizeof(*ii)));
  
  printf("test verify fn ... ok\n");
}

void
test_swap(void)
{
	int i1 = 0x1122, i2 = 0x3344;
	swap(&i1, &i2, sizeof(int));
	assert(0x1122 == i2 && 0x3344 == i1);
	int *p1 = &i1, *p2 = &i2;
	swap(&p1, &p2, sizeof(int*));
	assert(0x1122 == *p1 && 0x3344 == *p2);
	char *s1 = "abcdef", *s2 = "12345";
	swap(&s1, &s2, sizeof(char*));
	assert(strcmp("abcdef", s2) == 0 && strcmp("12345", s1) == 0);
	char sa1[] = "abcdef", sa2[] = "12345";
	char *ss1 = sa1, *ss2 = sa2;
	swap(&ss1, &ss2, sizeof(char*));
	assert(strcmp("abcdef", ss2) == 0 && strcmp("12345", ss1) == 0);
	printf("test swap macro ... ok\n");
}

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

	test_cmp_int();
	test_cmp_str();
  test_verify();
	test_swap();
	
	return 0;
}
#endif /* end of _ALGO_TEST_ */
