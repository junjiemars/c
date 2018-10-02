#include <_lang_.h>
#include <stdio.h>


/* syntax: typedef type declaration */
typedef int length_t;

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	length_t len1 = 123;
	printf("sizeof(length_t) = %zu\n", sizeof(len1));
}
