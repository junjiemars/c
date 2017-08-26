#include <sum.h>
#include <stdio.h>
#include <assert.h>

#ifdef MSVC
	#define io_fopen(f, n, m) fopen_s(&f, n, m);
	#define io_fprintf(f, ...) fprintf_s(f, __VA_ARGS__);
	#define io_fscanf(f, ...) fscanf_s(f, __VA_ARGS__);
#else
	#define io_fopen(f, n, m) f = fopen(n, m);
	#define io_fprintf(f, ...) fprintf(f, __VA_ARGS__);
	#define io_fscanf(f, ...) fscanf(f, __VA_ARGS__);
#endif

int 
out_seq(const char *f) {
	assert(f);

	int v = 1;
	FILE *out;

	io_fopen(out, f, "w");

	if (0 == out) {
		return v;
	}
	io_fprintf(out, "%s\n", "24 13 55 42 19 0");

	v = fclose(out);
	return v;
}

int 
sum_seq(const char *f) {
	assert(f);

	int num = 0, sum = 0, n = 0;
	FILE *in;

	io_fopen(in, f, "r+");

	if (0 == in) {
		return 1;
	}

	io_fscanf(in, "%d", &num);
	while (0 != num) {
		sum += num;
		n++;
		io_fscanf(in, "%d", &num);
	};
	io_fscanf(in, "%d", &num);

	io_fprintf(in, "%s\n", "----------");
	io_fprintf(in, "sum:%04d\n", sum);
	if (0 < n) {
		io_fprintf(in, "avg:%04d\n", sum/n);
	}

	fclose(in);

	return sum;
}

