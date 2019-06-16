#include <_algo_.h>

int comp_int(const void *lhs, const void *rhs);

void
bubble_sort(void *base, size_t nel, size_t width,
						int (*comp)(const void *, const void *)) {
	for (int i = 0; i < nel; i++) {
		for (int j = 0; i < nel - i - 1; j++) {
			if (comp(base[i], base[j]) > 0) {
				swap(base[i], base[j]);
			}
		}
	}
}

int
comp_int(const void *lhs, const void *rhs) {
	return *(const int*)lhs - *(const int*)rhs;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	

	return 0;
}
