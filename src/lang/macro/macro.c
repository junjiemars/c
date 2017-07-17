#include <lang.h>
#include "macro.h"
#include <stdio.h>
#include <string.h>


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

#define check_blank(a) strlen(#a)

#ifdef NM_HAVE_VARIADIC_MACRO

	#ifdef CC_MSVC
		#define io_sprintf(b, ...) sprintf_s(b, sizeof(b), __VA_ARGS__)
	#else
		#define io_sprintf(b, ...) sprintf(b, __VA_ARGS__)
	#endif

#endif

int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

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
  printf("sum(5, out)\n");
	sum(5, out);
	printf("out=%i, total=%i, |-  sum(%i)\n", out, total, 5);
	int i = 5;
	sum(i, out);
	printf("out=%i, total=%i, |-- sum(%i)\n", out, total, i);

	printf("----------\n");
#ifndef CC_MSVC
	/* C2168 msvc */
	printf("'%s' is blank strlen=%zu\n", "", check_blank());
#endif
	printf("%s is blank strlen=%zu\n", "123", check_blank(123));
	printf("%s is blank strlen=%zu\n", "abc", check_blank(abc));

#ifdef NM_HAVE_VARIADIC_MACRO
	printf("----------\n");
	char strbuf[32];
	io_sprintf(strbuf, "0x%x", 0xff00);
	printf("sprintf out=%s\n", strbuf);
#endif

}
