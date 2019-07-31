#include <_algo_.h>
#include <string.h>

void
list_array(const void *base, size_t nel, size_t width,
								void (*print)(const void *el)) {
	for (size_t i = 0; i < nel; i++) {
		print((char*) base + i * width);
	}
	printf("\n");
}

void
print_int(const void *el) {
	printf("%i, ", *(int*) el);
}

void
print_str(const void *el) {
	printf("%s, ", *(char**) el);
}

int
comp_int(const void *lhs, const void *rhs) {
	return *(const int*)lhs - *(const int*)rhs;
}

int
comp_str(const void *lhs, const void *rhs) {
	return strcmp(*(char**)lhs, *(char**)rhs);
}

#if _ALGO_
#include <assert.h>
#include <stdio.h>

void
test_comp_int(void) {
	int i1 = 0x1122, i2 = 0x3344;
	int cmp = comp_int((void*)&i1, (void*)&i2);
	assert(cmp < 0 && "comp_int(0x1122, 0x3344) should < 0");
	cmp = comp_int((void*)&i1, (void*)&i1);
	assert(cmp == 0 && "comp_int(0x1122, 0x1122) should == 0");
	cmp = comp_int((void*)&i2, (void*)&i1);
	assert(cmp > 0 && "comp_int(0x3344, 0x1122) should > 0");
	printf("test comp_int fn ... ok\n");
}

void
test_comp_str(void) {
	char *ss[] = { "abc", "123", };
	assert(0 == comp_str(ss+0*sizeof(*ss), ss+0*sizeof(*ss)));
	assert(0 != comp_str(ss+0*sizeof(*ss), ss+1*sizeof(*ss)));
	printf("test comp_str fn ... ok\n");
}

void
test_swap(void) {
	int i1 = 0x1122, i2 = 0x3344;
	swap(&i1, &i2);
	assert(0x1122 == i2 && 0x3344 == i1);
	char s1[] = "abc", s2[] = "123";
	swap(s1, s2);
	assert(strcmp("abc", s2) == 0 && strcmp("123", s1) == 0);
	printf("test swap macro ... ok\n");
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	test_comp_int();
	test_comp_str();
	test_swap();
	
	return 0;
}
#endif
