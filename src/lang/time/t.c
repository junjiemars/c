#include <_lang_.h>
#include <time.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	time_t epoch = time(0);
	printf("epoch(7/1/1970 UTC): %zu\n", epoch);


	struct tm *local = localtime(&epoch);
	printf("localtime: %s", asctime(local));
	time_t t_lt = timelocal(local);
	printf("time_t from localtime: %zu\n", t_lt);

	struct tm *gmt = gmtime(&epoch);
	printf("gmtime: %s", asctime(gmt));
	time_t t_gm = timegm(gmt);
	printf("time_t from gmtime: %zu\n", t_gm);

	printf("ctime: %s", ctime(&epoch));

	time_t end = epoch + 60*60*24;
	double d = difftime(end, epoch);
	printf("difftime(%zu, %zu) = %lf\n", end, epoch, d);

	return 0;
}
