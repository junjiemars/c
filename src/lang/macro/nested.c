#include <_lang_.h>
#include <stdio.h>

#define SQUARE(x) ((x)*(x))
#define CUBE(x) (SQUARE(x)*(x))

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	int x = SQUARE(3+3);
	int y = CUBE(3+3);
	printf("square(3)=%i, cube(3)=%i\n", x, y);
	
	return 0;
}
