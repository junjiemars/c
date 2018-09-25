#include <_lang_.h>
#include <stdio.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define E 2.71828
double e_squared = E * E;
#undef E


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
}
