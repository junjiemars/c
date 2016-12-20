#include <sum.h>
#include <stdio.h>

int out_seq(const char *f) {
	FILE *o;
#ifdef CC_MSVC
	fopen_s(&o, f, "w+");
#else
	o = fopen(f, "w+");
#endif

	if (0 == o) {
		return 1;
	}
	fprintf(o, "%s\n", "24 13 55 342 19 0");

	if (!o) fclose(o);
	return 0;
}

//int sum_seq(const char *f) {
//	f;
//	return 0;
//}

