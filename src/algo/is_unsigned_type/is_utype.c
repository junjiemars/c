#include <_algo_.h>
#include <stdio.h>


#define IS_UNSIGNED_TYPE(t) ((t)(-1) > 0)

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("is_unsigned_type(char)=%i\n", IS_UNSIGNED_TYPE(char));
	printf("is_unsigned_type(unsigned char)=%i\n", IS_UNSIGNED_TYPE(unsigned char));

	printf("is_unsigned_type(short)=%i\n", IS_UNSIGNED_TYPE(short));
	printf("is_unsigned_type(unsigned short)=%i\n", IS_UNSIGNED_TYPE(unsigned short));

	printf("is_unsigned_type(int)=%i\n", IS_UNSIGNED_TYPE(int));
	printf("is_unsigned_type(unsigned int)=%i\n", IS_UNSIGNED_TYPE(unsigned int));

	return 0;
}
