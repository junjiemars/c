#include <_lang_.h>

#ifdef static_assert
#undef static_assert
#endif

#define sa_cat_(a, b) a##b
#define sa_cat(a, b) sa_cat_(a, b)
#define static_assert(e, m) enum {sa_cat(line_, __LINE__) = 1/!!(e)}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	static_assert(1, "assert message");
	
	return 0;
}
