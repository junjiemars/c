#include <stdio.h>
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

