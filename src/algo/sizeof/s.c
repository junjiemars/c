#include <_algo_.h>


#define field_sizeof(t, f) sizeof(((t*)0)->f)
#define array_sizeof(a) (sizeof((a)) / sizeof((a)[0]))

struct point_s {
	short x;
	int y;
};

int a1[16];

int
main(void)
{
	assert(sizeof(short) == field_sizeof(struct point_s, x)
				 && "field_sizeof macro failed");

	assert(sizeof(int) == field_sizeof(struct point_s, y)
				 && "field_sizeof macro failed");

  assert(16 == array_sizeof(a1) && "array_sizeof failed");

  /* should failed to calculate sizeof ** */
	/* assert(array_sizeof(argv) == argc */
	/* 			 || "array_sizeof macro failed"); */

	return 0;
}
