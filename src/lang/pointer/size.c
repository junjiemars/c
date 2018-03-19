#include <_lang_.h>
#include <stdio.h>

#ifdef NM_HAVE_STDINT_H
#include <stdint.h>
#else
#include <stddef.h>
typedef unsigned __int64 uint64_t;
#endif


int
main(int argc, char **argv) {
  _unused_(argc);
  _unused_(argv);

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
