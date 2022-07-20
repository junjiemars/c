#include <_lang_.h>


int
main(void)
{
	printf("----------\n");
	printf("sizeof(void*)=%zu bytes\n", sizeof(void*));
	printf("sizeof(char*)=%zu bytes\n", sizeof(char*));
	printf("sizeof(short*)=%zu bytes\n", sizeof(short*));
	printf("sizeof(int*)=%zu bytes\n", sizeof(int*));
	printf("sizeof(long*)=%zu bytes\n", sizeof(long*));
	printf("sizeof(float*)=%zu bytes\n", sizeof(float*));
	printf("sizeof(double*)=%zu bytes\n", sizeof(double*));
	printf("sizeof(uint64_t*)=%zu bytes\n", sizeof(uint64_t*));
}
