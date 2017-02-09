#include <stdio.h>
#include "scope.h"

#define _unused_(x) ((void)(x))

/* file scope, declaration, definition with initializer  */
int i0 = 123;

/* file scope, declaration, tentative definition with initializer to 0 */
int i1;

/* file scope, extern declaration, must without initializer */
extern int i2;

/* function sub forward declaration */
void sub(int, int);

int main(int argc, char *argv[]) {
	_unused_(argv);

  printf("file scope: i0=%i\n", i0);

  int i0 = 321;
  printf("block scope in main: i0=%i\n", i0);

  {
    int i0 = 123+321;
    printf("block scope in main nested block: i0=%i\n", i0);
  }

  printf("block scope in main: i0=%i\n", i0);

  printf("function scope for function parameter: argc=%i\n", argc);
  {
    int argc = 123;
    printf("block scope in main nested block: argc=%i\n", argc);
  }

  if (i0 > 0) {
    goto i0;
		#ifdef CC_MSVC 
			#pragma warning(push)
			#pragma warning(disable: 4702)
			printf("this line bypassed via goto\n");
			#pragma warning(pop)
		#endif
  }

  {
    /* goto label has different namespace than objects,
     * so u can use i0 here
     */
    i0:
    printf("goto label i0 in main nested block, samed id with i0\n");
  }

  sub(i0, i0+1);

  {
    auto int i0 = 1;
    printf("auto int i0 in main nested block: i0=%i\n", i0);
  }

  printf("file scope, tentative definition: i1=%i\n", i1);

  printf("file scope, extern declaration: i2=%i\n", i2);


}

void sub(int i0, int i1) {
  printf("block scope in sub: i0=%i\n", i0+i1);

  /* well, the i0 from function parameter i0, so u can't redefined it */
  /* int i0 += 1; */
}
