#include <_lang_.h>
#include <stdio.h>
#include <stddef.h>
/* #include <limits.h> */
/* #include <inttypes.h> /\* C99 *\/ */

#if GCC
/* error: dereferencing type-punned pointer will break strict-aliasing
	 rules [-Werror=strict-aliasing] */
#  pragma GCC diagnostic ignored "-Wstrict-aliasing"
/* format ‘%zi’ expects argument of type ‘signed size_t’, but argument
	 3 has type ‘int’ [-Werror=format=] */
#  pragma GCC diagnostic ignored "-Wformat"
#elif CLANG
#  pragma clang diagnostic ignored "-Wformat"
#elif MSVC
/* warning C4477: 'printf' : format string '%zi' requires an argument
	 of type 'unsigned __int64', but variadic argument 2 has type
	 'int' */
#  pragma warning(disable : 4477)
#  include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif


void 
integer_type() {
	char c = 'a';
	short s = 0x1122;
  int i = 0x11223344;
	long l = 0x11223344;
	long long ll = 0x11223344aabbccdd;

	printf("char c/%zu = %zi, 0x%zx\n", 
				 sizeof(c), c, *(unsigned char*)&c);
	
	printf("short s/%zu = %zi, 0x%zx\n", 
				 sizeof(s), s, *(unsigned short*)&s);
	
	printf("int i/%zu = %zi, 0x%zx\n", 
				 sizeof(i), i, *(unsigned int*)&i);
	
	printf("long l/%zu = %zi, 0x%zx\n", 
				 sizeof(l), l, *(unsigned long*)&l);
	
	printf("long long ll/%zu = %zi, 0x%zx\n",
				 sizeof(ll), ll, *(unsigned long long*)&ll);
}

void 
float_type() {
  float f = 3.14f;
  double d = 2.7182L;
	long double ld = 2.1782;

	printf("float f/%zu = %f, 0x%zx\n", 
				 sizeof(f), f, *(unsigned int*)&f);
	
	printf("double d/%zu = %lf, 0x%zx\n", 
				 sizeof(d), d, *(unsigned long*)&d);
	
	printf("long double ld/%zu = %lf, 0x%zx\n",
				 sizeof(ld), ld, *(unsigned long long*)&ld);
}


int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\ninteger basic type\n");
	printf("--------------------\n");
  integer_type();

	printf("\nfloat type\n");
	printf("------------\n");
  float_type();

	printf("\nsize_t\n");
	printf("------------\n");	
	printf("sizeof(size_t) = %zu\n", sizeof(size_t));
	printf("sizeof(char) = %zu\n", sizeof(char));

	printf("\nssize_t\n");
	printf("------------\n");	
	printf("sizeof(ssize_t) = %zu\n", sizeof(ssize_t));

	printf("\nptrdiff_t\n");
	printf("------------\n");
	char s[] = "lang/type";
	ptrdiff_t p20 = &s[2]-&s[0];
	ptrdiff_t p02 = &s[0]-&s[2];
	printf("char s[%zu] = \"%s\"\n", sizeof(s)/sizeof(char), s);
	printf("ptrdiff_t of (&s[2]-&s[0]) is %td\n", p20);
	printf("ptrdiff_t of (&s[0]-&s[1]) is %td\n", p02);
}
