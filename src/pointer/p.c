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

	return 0;
}
