#include "_lang_.h"
#include <limits.h>
#include <inttypes.h>
#include <stdio.h>

void test_signed(void);

int 
main(void) {
  test_signed();
}

void
test_signed(void) {
  printf("%s: %02zu bytes\nMIN:%032i\nMAX: %031i\n",
         "char", sizeof(char), CHAR_MIN, CHAR_MAX);

  printf("%s: %02zu bytes\nMIN:%032i\nMAX: %031i\n",
         "short", sizeof(short), SHRT_MIN, SHRT_MAX);

  printf("%s: %02zu bytes\nMIN:%032i\nMAX: %031i\n",
         "int", sizeof(int), INT_MIN, INT_MAX);

  printf("%s: %02zu bytes\nMIN:%032li\nMAX: %031li\n",
         "long int", sizeof(long int), LONG_MIN, LONG_MAX);

  printf("%s: %02zu bytes\nMIN:%032lli\nMAX: %031lli\n",
         "long long int", sizeof(long long int), LLONG_MIN, LLONG_MAX);
}


/* void  */
/* test_integer_type(void) { */
/* 	char c = 'a'; */
/* 	short s = 0x1122; */
/*   int i = 0x11223344; */
/* 	long l = 0x11223344aabbccddL; */
/* 	long long ll = 0x11223344aabbccddLL; */

/* 	printf("%20s=%02zu, %020i, 0x%016x\n",  */
/* 				 "sizeof(char)", sizeof(c), c, *(unsigned char*)&c); */
	
/* 	printf("%20s=%02zu, %020i, 0x%016x\n", */
/* 				 "sizeof(short)", sizeof(s), s, *(unsigned short*)&s); */
	
/* 	printf("%20s=%02zu, %020i, 0x%016x\n", */
/* 				 "sizeof(int)", sizeof(i), i, *(unsigned int*)&i); */
	
/* 	printf("%20s=%02zu, %020li, 0x%016lx\n", */
/* 				 "sizeof(long)", sizeof(l), l, *(unsigned long*)&l); */
	
/* 	printf("%20s=%02zu, %020lli, 0x%016llx\n", */
/* 				 "sizeof(long long)", sizeof(ll), ll, *(unsigned long long*)&ll); */
/* } */





