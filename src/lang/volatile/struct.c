#include <_lang_.h>
#include <stdlib.h>
#include <stdio.h>

struct f1_s {
	int a;
};

struct f2_s {
	int a;
	int b;
};

struct f3_s {
	int volatile a;
	int volatile b;
};

int
raw_f1(struct f1_s *x) {
	x->a += 0x11;
	return x->a;
}

int
f1(volatile struct f1_s *x) {
	x->a += 0x11;
	return x->a;
}

int
raw_f2(struct f2_s *x) {
	x->a += 0x11;
	x->b += 0x2200;
	return (x->a + x->b);
}

int
f2(volatile struct f2_s *x) {
	x->a += 0x11;
	x->b += 0x2200;
	return (x->a + x->b);
}

int
f3(struct f3_s *x) {
	x->a += 0x11;
	x->b += 0x2200;
	return (x->a + x->b);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int sum = 0;
	volatile struct f1_s *x = malloc(sizeof(struct f1_s));
	sum = f1(x);
	free((struct f1_s*)x);
	printf("sum(f1)=0x%04x\n", sum);

	volatile struct f2_s *y = malloc(sizeof(struct f2_s));
	sum = f2(y);
	free((struct f2_s*)y);
	printf("sum(f2)=0x%04x\n", sum);

	struct f3_s *z = malloc(sizeof(struct f3_s));
	sum = f3(z);
	free(z);
	printf("sum(f3)=0x%04x\n", sum);
	
	return 0;
}
