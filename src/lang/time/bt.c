#include <_lang_.h>
#include <time.h>
#include <stdio.h>
#include <assert.h>

void
test_epoch(time_t *epoch) {
	if ((time_t) -1 == time(epoch)) {
		perror(0);
	} else {
		printf("epoch since 7/1/1970 UTC: %zu\n", *epoch);
	}
}

void
test_localtime(const time_t *epoch) {
  struct tm *local = localtime(epoch);
  _unused_(local);
}

void
test_timelocal(const time_t *epoch) {
  struct tm *local = localtime(epoch);
  time_t lacol = timelocal(local);
  assert(*epoch == lacol && "localtime <=> timelocal");
  char *asc = asctime(local);
  printf("asctime of localtime: %s", asc);
}

void
test_gmtime(const time_t *epoch) {
  struct tm *gm = gmtime(epoch);
  time_t mg = timegm(gm);
  assert(*epoch == mg);
  char *asc = asctime(gm);
  printf("asctime of gmtime: %s", asc);
}

void
test_ctime(const time_t *epoch) {
  char *c = ctime(epoch);
  printf("ctime of epoch: %s", c);
}

void
test_difftime(const time_t *epoch) {
  time_t end = (time_t)(*epoch + 60*60*24);
	double d = difftime(end, *epoch);
	printf("difftime(%zu, %zu) in seconds = %lf\n", end, *epoch, d);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

  time_t epoch;

  test_epoch(&epoch);
  test_localtime(&epoch);
  test_timelocal(&epoch);
  test_gmtime(&epoch);
  test_ctime(&epoch);
  test_difftime(&epoch);

	return 0;
}
