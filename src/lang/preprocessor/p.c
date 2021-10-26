#ident "(#) Identity, some compiler ignore it."

#include "_lang_.h"
#include <stdio.h>

#ifdef max
#  undef max
#endif
#define max(a, b) ((a) > (b) ? (a) : (b))

#ifdef min
#  undef min
#endif
#define min(a, b) ((a) < (b) ? (a) : (b))


#ifdef E
#  undef E
#endif
#define E 2.71828
double e_squared = E * E;
#undef E


#if defined( _ERROR_ ) && ( 1 == _ERROR_ )
#  error "compile failed: because _ERROR_==1 is true"
#endif


#if defined(MSVC)
#  pragma warning(disable:4996) /*_CRT_SECURE_NO_WARNINGS*/
#endif


#if (GCC)
#  pragma GCC diagnostic ignored "-Wstrict-aliasing"  /* (unsigned init*)&f: */
#endif


#if defined(str)
#  undef str
#endif
#define str(x)  #x

#if defined(log)
#  undef log
#endif
#define log(h, m) fprintf(stderr, "%s: %s\n", (h), (str(m)));


enum color
  {
    RED,
    GREEN,
    BLUE
  };
#define COLOR_STR(x) #x


#define defvar(type, var, val) type var_##var = val


int
main(int argc, char *argv[])
{
	_unused_(argc);
	_unused_(argv);

	char *platform = 
#if defined(LINUX)
    "Linux";
#elif defined(DARWIN)
	"Darwin";
#elif defined(WINNT)
  "WinNT";
#else
	"unknown platform";
#endif

  char *compiler =
#if (CLANG)
    "clang";
#elif (GCC)
  "gcc";
#elif (MSVC)
  "msvc";
#else
  "unknown compiler";
#endif

	printf("platform: %s\n", platform);
  printf("compiler: %s\n", compiler);
	printf("max: %i in [%i %i]\n", max(0, 1), 0, 1);
	printf("min: %i in [%i %i]\n", min(0, 1), 0, 1);
  printf("min + max: %i in [%i %i]\n", min(0, 1) + max(0, 1), 0, 1);
	printf("E^2: %f\n", e_squared);

	log("__FILE__", __FILE__);

  /* char s[8] = {0}; */
	/* snprintf(s, sizeof(s), "%i", __LINE__); */
	log("__LINE__", __LINE__);

	log("__DATE__", __DATE__);
	log("__TIME__", __TIME__);
	log("__TIMESTAMP__", __TIMESTAMP__);

	printf("color: %s\n", COLOR_STR(RED));
	printf("color: %s\n", COLOR_STR(BLUE));

	defvar(int, x, 1);
	defvar(double, y, e_squared);
	printf("defvar var_x=%i\n", var_x);
	printf("defvar var_y=%f\n", var_y);

	return 0;
}
