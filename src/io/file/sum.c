#include <stdio.h>
#include <sum.h>

int out_seq(const char *f) {
	FILE *o = fopen(f, "w+");
	if (0 == o) {
		return 1;
	}
	fprintf(o, "%s\n", "24 13 55 342 19 0");

	if (!o) fclose(o);
	return 0;
}

int sum_seq(const char *f) {
	return 0;
}

