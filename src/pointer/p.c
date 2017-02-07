#include <stdio.h>
#include <stdint.h>

int main(){
	printf("----------\n");
	char* ss[] = {"first", "second", "third", NULL/*must has*/ };
	for (char** p=ss; *p != NULL; p++) {
		printf("%s ", p[0]);
	}
	printf("\naddress of the list is:%p\n", ss);

	printf("----------\n");
	printf("sizeof(char*)=%zu bytes\n", sizeof(char*));
	printf("sizeof(short*)=%zu bytes\n", sizeof(short*));
	printf("sizeof(int*)=%zu bytes\n", sizeof(int*));
	printf("sizeof(long*)=%zu bytes\n", sizeof(long*));
	printf("sizeof(float*)=%zu bytes\n", sizeof(float*));
	printf("sizeof(double*)=%zu bytes\n", sizeof(double*));
	printf("sizeof(uint64_t*)=%zu bytes\n", sizeof(uint64_t*));

	printf("----------\n");
	int v1 = 0x11223344, v2 = 0x44332211;
	const int* p1 = &v1;
	*(int**)&p1 = &v2;
	printf("<const int*>: p1=%d\n", *p1);

	int* const p2 = &v1;
	*(const int**)&p2 = &v2;
	printf("<int* const>: p2=%d\n", *p2);

	const int* const p3 = &v1;
	*(int**)&p3 = &v2;
	printf("<const int* const>: p3=%d\n", *p3);
	*(int**)&p3 = &v1;
	printf("<const int* const>: p3=%d\n", *p3);

	return 0;
}
