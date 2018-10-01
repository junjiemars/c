#include <_lang_.h>
#include "macro.h"
#include <stdio.h>
#include <string.h>


#define double_v1(x) 2*x
#define double_v2(x) (2*(x))

#define max(a, b) ((a) > (b) ? (a) : (b))

#define incr_v1(a, b)      \
	(a)++;									 \
	(b)++;

#define incr_v2(a, b) {    \
	(a)++;                   \
	(b)++;                   \
}

#define sum(max, out) {              								\
	int total_g123 = 0, max_g124=max;  								\
	for (int i_g125=0; i_g125<max_g124; i_g125++)    	\
		total_g123 += i_g125;              							\
	out = total_g123;                  								\
}

#define check_blank(a) strlen(#a)

#ifdef NM_HAVE_VARIADIC_MACRO
#  if defined(NM_HAVE_SPRINTF_S)
#    define io_sprintf(b, ...) sprintf_s(b, sizeof(b), __VA_ARGS__)
#  elif defined(NM_HAVE_SNPRINTF)
#    define io_sprintf(b, ...) snprintf(b, sizeof(b), __VA_ARGS__)
#  else
#    define io_sprintf(b, ...) sprintf(b, __VA_ARGS__)
#  endif
#endif

int 
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\ndouble macro\n");
	printf("--------------\n");
	printf("double_v1(1+1)*8=%i\n", double_v1(1+1)*8);
	printf("double_v2(1+1)*8=%i\n", double_v2(1+1)*8);

	printf("\nmax macro\n");
	printf("-----------\n");
	int a = 1, b = 2;
	printf("a=%i, b=%i, |+ max\n", a, b);
	printf("max(a,b++)=%i\n", max(a,b++));
	printf("a=%i, b=%i, |- max\n", a, b);

	printf("\nincr macro\n");
	printf("------------\n");
	a = 1, b = 2;
	printf("a=%i, b=%i, |+ incr_v1\n", a, b);
	if (a > b) incr_v1(a, b);
	printf("if (a > b) incr_v1(a, b)\n");
	printf("a=%i, b=%i, |- incr_v1\n", a, b);
	
	printf("------------\n");
	a = 1, b = 2;
	printf("a=%i, b=%i, |+ incr_v2\n", a, b);
	if (a > b) incr_v2(a, b);
	printf("if (a > b) incr_v2(a, b)\n");
	printf("a=%i, b=%i, |- incr_v2\n", a, b);
	
	printf("----------\n");
	int total = 5, out;
  printf("sum(5, out)\n");
	sum(5, out);
	printf("out=%i, total=%i, |-  sum(%i)\n", out, total, 5);
	int i = 5;
	sum(i, out);
	printf("out=%i, total=%i, |-- sum(%i)\n", out, total, i);

	printf("----------\n");
#ifndef MSVC
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
