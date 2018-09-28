#include <_lang_.h>
#include <stdio.h>
#include <stddef.h>


#if GCC
/* error: format ‘%zx’ expects argument of type ‘size_t’,
   but argument 3 has type ‘long unsigned int’ 
	 [-Werror=format] */
# pragma GCC diagnostic ignored "-Wformat"
#elif MSVC
/* C4477: 'printf' : format string '%llu' requires 
   an argument of type 'unsigned __int64', but variadic 
   argument 2 has type 'unsigned long' */
# pragma warning(disable:4477)
#endif

void 
integer_type() {
	char c = 'a';
	short int s = 0x1122; /* eq: short s = 0x1122; */
  int i = 10;
  long int l = 100L; /* eq: long l = 100L; */

	printf("a %i stored as 0x%02x\n", c, *(unsigned char*)&c);
	printf("0x1122 %i stored as 0x%04x\n", s, *(unsigned short*)&s);
  printf("ten %i stored as 0x%08x\n", i, *(unsigned int*)&i);
  printf("hundred %li stored as 0x%08zx\n", l, *(unsigned long*)&l);
}

void 
float_type() {
  float f = 3.14f;
  double d = 2.7182L;
  printf("pi %f stored as 0x%8x\n", f, *(unsigned int*)&f);
  printf("e %lf stored as 0x%8zx\n", d, *(unsigned long*)&d);
}


int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	printf("\ninteger type\n");
	printf("------------\n");
  integer_type();

	printf("\nfloat type\n");
	printf("------------\n");
  float_type();

	printf("\nsize_t\n");
	printf("------------\n");	
	printf("sizeof(char) = %zu\n", sizeof(char));

	printf("\nptrdiff_t\n");
	printf("------------\n");
	char s[] = "language/type";
	ptrdiff_t p20 = &s[2]-&s[0];
	ptrdiff_t p02 = &s[0]-&s[2];
	printf("char s[%zu] = \"%s\"\n", sizeof(s)/sizeof(char), s);
	printf("ptrdiff_t of (&s[2]-&s[0]) is %td\n", p20);
	printf("ptrdiff_t of (&s[0]-&s[1]) is %td\n", p02);
}
