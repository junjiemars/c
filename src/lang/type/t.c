#include "_lang_.h"
#include <stdio.h>
#include <stddef.h>


#if MSVC
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif


void 
test_integer_type(void) {
	char c = 'a';
	short s = 0x1122;
  int i = 0x11223344;
	long l = 0x11223344aabbccddL;
	long long ll = 0x11223344aabbccddLL;

	printf("%20s=%02zu, %020i, 0x%016x\n", 
				 "sizeof(char)", sizeof(c), c, *(unsigned char*)&c);
	
	printf("%20s=%02zu, %020i, 0x%016x\n",
				 "sizeof(short)", sizeof(s), s, *(unsigned short*)&s);
	
	printf("%20s=%02zu, %020i, 0x%016x\n",
				 "sizeof(int)", sizeof(i), i, *(unsigned int*)&i);
	
	printf("%20s=%02zu, %020li, 0x%016lx\n",
				 "sizeof(long)", sizeof(l), l, *(unsigned long*)&l);
	
	printf("%20s=%02zu, %020lli, 0x%016llx\n",
				 "sizeof(long long)", sizeof(ll), ll, *(unsigned long long*)&ll);
}

void
test_float_type(void) {
  float f = 3.14f;
  double d = 2.7182; /* non suffix means double */
	long double ld = 2.718281828459L;

	printf("%20s=%02zu, %020f, 0x%016x\n",
				 "sizeof(float)", sizeof(f), f, *(unsigned int*)&f);
	
	printf("%20s=%02zu, %020lf, 0x%16lx\n",
				 "sizeof(double)", sizeof(d), d, *(unsigned long*)&d);
	
	printf("%20s=%02zu, %020Lf, 0x%16llx\n",
				 "sizeof(long double)", sizeof(ld), ld, *(unsigned long long*)&ld);
}

void
test_size_type(void) {
  size_t st = 0x11223344;
  ssize_t sst = 0x11223344;
  
  printf("%20s=%02zu, %020zu, 0x%016lx\n",
         "sizeof(size_t)", sizeof(st), st, *(unsigned long*)&st);
  printf("%20s=%02zu, %020zi, 0x%016lx\n",
         "sizeof(ssize_t)", sizeof(sst), sst, *(unsigned long*)&sst);
}

void
test_pointer_type(void) {
	char s[] = "lang/type";
	ptrdiff_t p20 = &s[2]-&s[0];
	ptrdiff_t p02 = &s[0]-&s[2];

	printf("%20s=%02zu, %20s, %p\n",
         "sizeof(char*0)", sizeof(&s[0]), s, (unsigned long*)&s[0]);
	printf("%20s=%02zu, %20s, %p\n",
         "sizeof(char*1)", sizeof(&s[1]), s, (unsigned long*)&s[1]);
	printf("%20s=%02zu, %20s, %p\n",
         "sizeof(char*2)", sizeof(&s[2]), s, (unsigned long*)&s[2]);
	printf("%20s=%02zu, %020td\n",
         "sizeof(ptrdiff_t)", sizeof(p20), p20);
	printf("%20s=%02zu, %020td\n",
         "sizeof(ptrdiff_t)", sizeof(p02), p02);
}


int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\ninteger type\n");
	printf("--------------------\n");
  test_integer_type();

	printf("\nfloat type\n");
	printf("------------\n");
  test_float_type();

	printf("\nsize type\n");
	printf("------------\n");
  test_size_type();

	printf("\npointer type\n");
	printf("------------\n");
  test_pointer_type();
}
