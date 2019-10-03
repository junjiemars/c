#include <_lang_.h>
#include <stdio.h>

/* ./configure --has-lang --with-optimize=-O1 */


#if !( NM_HAVE_RESTRICT_KEYWORD )
#  if ( NM_HAVE___RESTRICT_KEYWORD )
#    define restrict __restrict
#  else
#    define restrict
#  endif
#endif


void
f1(int *p1, int *p2, int *val) {
	*p1 += *val;
	*p2 += *val;
}

void
f2(int *p1, int *p2, int *restrict val) {
	*p1 += *val;
	*p2 += *val;
}


int
main(int argc, char **argv) {
	_unused_(argv);

	printf("support restrict keyword = %s\n----------\n",
#if ( NM_HAVE_RESTRICT_KEYWORD ) || ( NM_HAVE___RESTRICT_KEYWORD )
				 "yes"
#else
				 "no"
#endif
				 );

	int x = argc;
	int y = argc * 10;
	int z = argc * 100;
	
	f1(&x, &y, &z);
	printf("x=%d, y=%d, z=%d\n", x, y, z);

	f2(&x, &y, &z);
	printf("x=%d, y=%d, z=%d\n", x, y, z);

	return 0;
}
