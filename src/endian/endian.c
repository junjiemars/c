#include <stdio.h>
#include <stdint.h>

int is_little_endian() {
	int i = 0x11223344;
	char *p = (char *)&i;

	if (0x44 == *p) return 1;
	return 0;
}

int is_big_endian() {
	static union {
		uint32_t u;
		char c[4];
	} e = { 0x01000000 };
	return e.c[0];
}

int main(int argc, const char *argv[]) {

	int e1 = is_little_endian();
	printf("little endian \t= %s\n", e1 ? "yes" : "no");

	int e2 = is_big_endian();
	printf("big endian \t= %s\n", e2 ? "yes" : "no");

	return 0;
}
