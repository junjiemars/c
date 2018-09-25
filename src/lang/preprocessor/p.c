#include <_lang_.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define E 2.71828
double e_squared = E * E;
#undef E

#if !defined(MIN)
# define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#if (1==_ERROR_)
# error "compile failed: because _ERROR_==1 is true"
#endif

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	char platform[]
#if defined(LINUX)
  = "Linux";
#elif defined(DARWIN)
	= "Darwin";
#else
	= "Unknown";
#endif

	printf("platform: %s\n", platform);
	printf("max: %i in [%i %i]\n", MAX(0,1), 0, 1);
	printf("E^2: %f\n", e_squared);
	printf("min: %i in [%i %i]\n", MIN(0,1), 0, 1);
}
