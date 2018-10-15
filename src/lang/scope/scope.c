#include <_lang_.h>
#include "scope.h"
#include <stdio.h>
#include <assert.h>


/* file scope, declaration, definition with initializer  */
int i0 = 123;

/* file scope, declaration, tentative definition with initializer to
	 0 */
int i1;

/* file scope, extern declaration, must without initializer */
extern int i2;

/* function sub forward declaration */
/* extern keyword is optional */
void sub(int, int);

int 
inc() {
	static int i=0;
	return i++;
}

#ifdef MSVC
int map(int (*fn)(int n), int *a) {
#else
int map(int (*fn)(int n), int a[static 4]) {
#endif
	for (int i=0; i<4; ++i) {
		a[i] = (*fn)(a[i]);
	}
	return 4;
}

int
 main(int argc, char *argv[]) {
	_unused_(argv);

	printf("epoch: i0=%i, i1=%i, i2=%i\n", i0, i1, i2);

	printf("----------file scope----------\n");
  printf("=>main{i0}=%i\n", i0);


	printf("----------block scope----------\n");
  int i0 = 321;
  printf("=>main{i0}=%i\n", i0);

  {
    int i0 = 123+321;
    printf("=>main{{i0}}=%i\n", i0);
  }

  printf("=>main{i0}=%i\n", i0);

  printf("=>main{argc}=%i\n", argc);

  {
    int argc = 123;
    printf("=>main{{argc}}=%i\n", argc);
  }

  if (i0 > 0) {
		printf("=>main{{goto i0}}=>{{i0:}}\n");
    goto i0;
    printf("this line bypassed via goto\n");
  }

  {
    /* goto label has different namespace than objects,
     * so u can use i0 here
     */
    i0:
    printf("=>main{{i0:}}\n");
  }

	printf("----------fn scope----------\n");
  sub(i0, i0+1);

	printf("----------block scope----------\n");
  {
    auto int i0 = 1;
    printf("=>main{{auto i0}}=%i\n", i0);
  }

	printf("----------file scope----------\n");
  printf("=>main{i1}=%i\n", i1);

  printf("=>main{extern int}:i2=%i\n", i2);

	printf("=>main=>{extern inline fn}:sqr(%i)=%i\n", i2, sqr(i2));

	printf("=>main=>{fn}:inc()=%i\n", inc());
	printf("=>main=>{fn}:inc()=%i\n", inc());

	int a[] = { 1, 2, 3, 4 };
	printf("=>main=>{fn}:map({1,2,3,4},&sqr)=%i\n", map(&sqr, a));
	for (size_t i=0; i<sizeof(a)/sizeof(a[0]); ++i) {
		printf("%i ", a[i]);
	}
	putchar('\n');
	
	register int k, sum;
	for (k=1, sum=0; k < 6; sum += k, k++);
	printf("=>main{for:register:1+2...+5}=%i\n", sum);
}

void 
sub(int i0, int i1) {
  printf("=>sub{i0=%i+i1=%i}=%i\n", i0, i1, i0+i1);

  /* well, the i0 from function parameter i0, so u can't redefined it */
  /* int i0 += 1; */
}
