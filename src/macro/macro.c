#include <macro.h>
#include <stdio.h>
#include <string.h>

#define _unused_(x) ((void)(x))

#define double_v1(x) 2*x
#define double_v2(x) (2*(x))

#define max(a, b) ((a) > (b) ? (a) : (b))

#define incr(a, b)      \
    (a)++;              \
    (b)++;

#define sum(max, out) {              								\
	int total_g123 = 0, max_g124=max;  								\
	for (int i_g125=0; i_g125<max_g124; i_g125++)    	\
		total_g123 += i_g125;              							\
	out = total_g123;                  								\
}

/*
#define check_blank(a) {                            \
	int v = (strlen(#a)>0) ? (a+0) : 2;               \
	printf("I understand ur input to be %i.\n", v);   \
}
*/

int main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

#if (CC_MSVC)
	W_C4100(argc)
	W_C4100(argv)
#endif

	printf("----------\n");
	printf("double_v1(1+1)*8=%i\n", double_v1(1+1)*8);
	printf("double_v2(1+1)*8=%i\n", double_v2(1+1)*8);

	printf("----------\n");
	int a = 1, b = 2;
	printf("a=%i, b=%i, |+ max\n", a, b);
	printf("max(a,b++)=%i\n", max(a,b++));
	printf("a=%i, b=%i, |- max\n", a, b);

	printf("----------\n");
	printf("a=%i, b=%i, |+ incr\n", a, b);
	if (a > b) incr(a, b);
	printf("a=%i, b=%i, |- incr\n", a, b);


	printf("----------\n");
	int total = 5, out;
	sum(5, out);
	printf("out=%i, total=%i, |+ sum\n", out, total);
	int i = 5;
	sum(i, out);
	printf("out=%i, total=%i, |- sum\n", out, total);

	/*
	check_blank(0);
	check_blank();
	*/
}
