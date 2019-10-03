#include <_lang_.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>


int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	time_t epoch;
	if ((time_t) -1 == time(&epoch)) {
		perror(0);
	} else {
		printf("epoch(7/1/1970 UTC): %zu\n", epoch);
	}

	struct tm *local = localtime(&epoch);
	char *asc1 = asctime(local);
	printf("localtime: %s", asc1);
	time_t t_lt = timelocal(local);
	printf("time_t from localtime: %zu\n", t_lt);

	struct tm *gmt = gmtime(&epoch);
	char *asc2 = asctime(gmt);
	printf("gmtime: %s", asc2);
	time_t t_gm = timegm(gmt);
	printf("time_t from gmtime: %zu\n", t_gm);

	assert(asc1 == asc2 && "static inside asctime fn");

	printf("ctime: %s", ctime(&epoch));

	time_t end = epoch + 60*60*24;
	double d = difftime(end, epoch);
	printf("difftime(%zu, %zu) = %lf\n", end, epoch, d);

	return 0;
}
