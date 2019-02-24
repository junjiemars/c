#include <_lang_.h>
#include <time.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	time_t epoch = time(0);
	struct tm *local = localtime(&epoch);
	
	printf("local: %s\n", asctime(local));
	return 0;
}
