#include <stdio.h>
#include <string.h>

/*
 * 1) expression-type macro: parens or avoid double usage
 * 2) block-type macro
 * 3) use: cc -E macro.c just to run preprocessor
 */

#define double_v1(x) 2*x
#define double_v2(x) (2*(x))

#define max(a, b) ((a) > (b) ? (a) : (b))

#define need_blocked(a, b)      \
    (a)++;                      \
    (b)++;

#define sum(max, out) {              \
	int total = 0, max_g123=max;       \
	for (int i=0; i<max_g123; i++)     \
		total += i;                      \
	out = total;                       \
}

//#define check_blank(a) {                            \
//	int v = (strlen(#a)>0) ? (a+0) : 2;               \
//	printf("I understand ur input to be %i.\n", v);   \
//}

int main(int argc, char *argv[]) {
	printf("----------\n");
	printf("double_v1(1+1)*8=%i\n", double_v1(1+1)*8);
	printf("double_v2(1+1)*8=%i\n", double_v2(1+1)*8);

	printf("----------\n");
	int a = 1, b = 2;
	printf("a=%i, b=%i, |+ max\n", a, b);
	printf("max(a,b++)=%i\n", max(a,b++));
	printf("a=%i, b=%i, |- max\n", a, b);

	printf("----------\n");
	printf("a=%i, b=%i, |+ need_blocked\n", a, b);
	if (a > b) need_blocked(a, b);
	printf("a=%i, b=%i, |- need_blocked\n", a, b);


	printf("----------\n");
	int total = 5, out;
	sum(5, out);
	printf("out=%i, original total=%i\n", out, total);
	int i = 5;
	sum(i, out);
	printf("out=%i, original total=%i\n", out, total);

	//check_blank(0);
	//check_blank();
}
