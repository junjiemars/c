#include <_lang_.h>
#include <time.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	clock_t clock_per_seconds = clock();
	if ((clock_t) -1 == clock_per_seconds) {
		perror(0);
	} else {
		printf("amount of processor time: %zu\n", clock_per_seconds);
	}
	return 0;
}
