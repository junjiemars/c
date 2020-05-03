#include <_lang_.h>
#include <stdio.h>


#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define E 2.71828
double e_squared = E * E;
#undef E

#if !defined(MIN)
#  define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#if defined( _ERROR_ ) && ( 1 == _ERROR_ )
#  error "compile failed: because _ERROR_==1 is true"
#endif

#ifdef MSVC
#  pragma warning(disable:4996) /*_CRT_SECURE_NO_WARNINGS*/
#endif

#if ( GCC )
#  pragma GCC diagnostic ignored "-Wstrict-aliasing"  /* (unsigned init*)&f: */
#endif

void
_log_(const char *header, const char *message) {
	fprintf(stderr, "%s: %s\n", header, message);
}

enum Color {
	RED,
	GREEN,
	BLUE
};
#define COLOR_STR(x) #x


#define DEFVAR(type, var, val) type var_##var = val;


int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	char platform[]
#if defined( LINUX )
  = "Linux";
#elif defined( DARWIN )
	= "Darwin";
#else
	= "Unknown";
#endif

	printf("platform: %s\n", platform);
	printf("max: %i in [%i %i]\n", MAX(0,1), 0, 1);
	printf("E^2: %f\n", e_squared);
	printf("min: %i in [%i %i]\n", MIN(0,1), 0, 1);

	char s[256] = {0};
	
	_log_("__FILE__", __FILE__);
	
	snprintf(s, sizeof(s), "%i", __LINE__);
	_log_("__LINE__", s);

	_log_("__DATE__", __DATE__);
	_log_("__TIME__", __TIME__);
	_log_("__TIMESTAMP__", __TIMESTAMP__);

	printf("color: %s\n", COLOR_STR(RED));
	printf("color: %s\n", COLOR_STR(BLUE));

	DEFVAR(int, x, 1);
	DEFVAR(double, y, e_squared);
	printf("defvar x=%i\n", var_x);
	printf("defvar y=%f\n", var_y);

	/* printf */
  /* #include "p.txt" */
	/* ; */

	return 0;
}
