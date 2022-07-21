#include "_algo_.h"


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

void
print_size_t(const void *el)
{
	printf("%zu, ", *(size_t*) el);
}

void
print_score_s(const void *e)
{
  const struct score_s *ss = (struct score_s *) e;
  printf("name = %s, score = %d\n", ss->name, ss->score);
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
cmp_score_s(const void *lhs, const void *rhs)
{
  const struct score_s *s1 = (const struct score_s*) lhs;
  const struct score_s *s2 = (const struct score_s*) rhs;
  return s1->score - s2->score;
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
	int  i1  =  0x1122;
  int  i2  =  0x3344;
	__attribute__((unused)) int cmp = cmp_int(&i1, &i2);

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

	assert(0 == cmp_str(&s1, &ss[1]));
	printf("test cmp_str fn ... ok\n");
}

void
test_verify(void)
{
	char *ss[] = { "abc", "12345" };
  size_t s1 = strlen(ss[0]);
  size_t s2 = strlen(ss[1]);
  assert(0 == verify(&ss[0], &ss[0], _min_(s1, s1)));
  assert(0 != verify(&ss[0], &ss[1], _min_(s1, s2)));

  int ii[] = { 1234, 12345 };
  assert(0 == verify(&ii[0], &ii[0], sizeof(*ii)));
  assert(0 != verify(&ii[0], &ii[1], sizeof(*ii)));

  printf("test verify fn ... ok\n");
}


int
main(void)
{
	test_cmp_int();
	test_cmp_str();
  test_verify();

	return 0;
}
#endif /* end of _ALGO_TEST_ */
