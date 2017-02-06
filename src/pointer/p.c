#include <stdio.h>
#include <stdint.h>

int main(){
	printf("----------\n");
	char *list[] = {"first", "second", "third", NULL/*must has*/};
	for (char **p=list; *p != NULL; p++){
		printf("%s\n", p[0]);
	}
	printf("address of the list is:%p\n", list);

	printf("----------\n");
	printf("sizeof(char*)=%lu bytes\n", sizeof(char*));
	printf("sizeof(short*)=%lu bytes\n", sizeof(short*));
	printf("sizeof(int*)=%lu bytes\n", sizeof(int*));
	printf("sizeof(long*)=%lu bytes\n", sizeof(long*));
	printf("sizeof(float*)=%lu bytes\n", sizeof(float*));
	printf("sizeof(double*)=%lu bytes\n", sizeof(double*));
	printf("sizeof(uint64_t*)=%lu bytes\n", sizeof(uint64_t*));

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
