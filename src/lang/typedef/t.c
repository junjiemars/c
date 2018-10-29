#include <_lang_.h>
#include <stdio.h>


/* syntax: typedef type declaration */
typedef int length_t;

struct point_s /* tag: not type */ {
	int x;
	int y;
};
typedef struct point_s point_s;

typedef struct point1_s {
	int x;
	int y;
} point1_s /* type */;


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	length_t len1 = 123;
	printf("sizeof(length_t) = %zu\n", sizeof(len1));
}
