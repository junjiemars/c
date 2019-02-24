#include <_lang_.h>
#include <time.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	time_t epoch = time(0);
	printf("epoch seconds: %ld\n", epoch);

	return 0;
}
