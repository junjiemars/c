#include <_memory_.h>
#include <string.h>
#include <stdio.h>

void
swap(void *a, void *b, size_t size) {
	uint8_t buffer[size];	
	memcpy(buffer, a, size);
	memcpy(a, b, size);
	memcpy(b, buffer, size);
}

void
swap_test() {
	int i1 = 0x11223344, i2 = 0x44332211;
	printf("swap(0x%x, 0x%x, %zu) \t => ", i1, i2, sizeof(int));
	swap(&i1, &i2, sizeof(int));
	printf("0x%x \t 0x%x\n", i1, i2);

	int32_t i32 = 0x11223344;
	int32_t _gap_ = 0; _unused_(_gap_);
	int16_t i16 = 0x7788; 
	printf("swap(0x%x, 0x%x, %zu) \t\t => ", i32, i16, sizeof(int16_t));
	swap(&i32, &i16, sizeof(int16_t));
	printf("0x%x \t 0x%x\n", i32, i16);

	#ifdef RISKY 
		// 1) use $(nm_def_opt)RISKY=1 in makefile;
		// 2) or, use CFLAGS=-DRISKY=1 in make command lien;
		printf("swap(0x%x, 0x%x, %zu) \t\t => ", i32, i16, sizeof(int32_t));
		swap(&i32, &i16, sizeof(int32_t));
		printf("0x%x \t 0x%x | 0x%x\n", i32, i16, _gap_);
	#endif


	char c1[64] = "hello", c2[64] = "world";
	printf("swap(%s, %s, %zu) \t\t\t => ", c1, c2, sizeof(char)*64);
	swap(c1, c2, sizeof(char)*64);
	printf("%s \t %s\n", c1, c2);

	// smart: no memory swapping just pointer swapping
	printf("swap(%p, %p, %zu)  => ", &c1, &c2, sizeof(char*));
	swap(&c1, &c2, sizeof(char*));
	printf("%s \t %s\n", c1, c2);
}

void* 
linear_search(void *key, void *base, size_t n, size_t size, 
	int (*test)(const void *x, const void*y, size_t size)) {

	for (size_t i = 0; i < n; i++) {
		void *a = (uint8_t*)base + i*size;
		if (0 == test(key, a, size)) {
			return a;
		}
	}

	return 0;
}

int
test_str(const void *x, const void *y, size_t size) {
	const char* a = *(const char**)x;
	const char* b = *(const char**)y;
	return strncmp(a, b, size);
}

void
linear_search_test() {
	int ia[] = { 1, 9, 7, 0, 4, 5 };
	int ikey = 7;
	printf("linear_search(%i) \t\t => ", ikey);
	int *i = linear_search(&ikey, ia, _sizeof_array_(ia), sizeof(int), memcmp);
	printf("%i \t\t|\t %p\n", *i, i);

	char ca[] = "hello, world!";
	char ckey = 'r';
	printf("linear_search('%c') \t\t => ", ckey);
	char *c = linear_search(&ckey, ca, _sizeof_array_(ca), sizeof(char), memcmp);
	printf("'%c' \t|\t %p\n", *c, c);

	char *sa[] = {"Lisp", "MaCarthy", "Russell"};
	char *skey = "MaCarthy";
	printf("linear_search(\"%s\") \t => ", skey);
	char **s = linear_search(&skey, &sa, _sizeof_array_(sa), sizeof(char*), test_str);
	printf("\"%s\" \t|\t %p\n", *s, s);
}


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\n*%s ENDIAN*\n", NM_HAVE_LITTLE_ENDIAN ? "LITTLE" : "BIG");
	printf("----------\n");

	swap_test();
	linear_search_test();
}
