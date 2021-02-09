#include <_lang_.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

# if !defined(__USE_MISC)
#   define __USE_MISC
# endif

#include <time.h>

void test_epoch(time_t *);
void test_localtime(const time_t *);

#if !(MSVC)
void test_timelocal(const time_t *);
#endif  /* end of !MSVC */

void test_gmtime(const time_t *);
void test_ctime(const time_t *);
void test_difftime(const time_t *);
void test_mktime(const time_t *);

void
test_epoch(time_t *epoch)
{
	if ((time_t) -1 == time(epoch))
    {
      perror(0);
      return;
    }
  printf("epoch since 1/1/1970 UTC: %zu\n", *epoch);
}

void
test_localtime(const time_t *epoch)
{
  struct tm *local = localtime(epoch);
  _unused_(local);
}

#if !(MSVC)
void
test_timelocal(const time_t *epoch)
{
  struct tm *local = localtime(epoch);
  time_t lacol = timelocal(local);
  ASSERT(*epoch == lacol && "localtime <=> timelocal");
  char *asc = asctime(local);
  printf("asctime of localtime: %s", asc);
}
#endif  /* end of !MSVC */

void
test_gmtime(const time_t *epoch)
{
  struct tm *gm = gmtime(epoch);
  time_t mg = timegm(gm);
  ASSERT(*epoch == mg);
  char *asc = asctime(gm);
  printf("asctime of gmtime: %s", asc);
}

void
test_ctime(const time_t *epoch)
{
  char *c = ctime(epoch);
  char *c1 = asctime(localtime(epoch));
  ASSERT(0 == strcmp(c, c1));
  printf("ctime of epoch: %s", c);
}

void
test_difftime(const time_t *epoch)
{
  time_t end = (time_t) (*epoch + 60*60*24);
	double d = difftime(end, *epoch);
	printf("difftime(%zu, %zu) in seconds = %lf\n", end, *epoch, d);
}

void
test_mktime(const time_t *epoch)
{
  struct tm *local = gmtime(epoch);
  local->tm_year++;
  char *asc = asctime(local);
  printf("asctime of localtime: %s", asc);  
}

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

  time_t epoch = 0;

  test_epoch(&epoch);

  test_localtime(&epoch);

#if !(MSVC)
  test_timelocal(&epoch);
#endif  /* end of !MSVC */

  test_gmtime(&epoch);
  test_ctime(&epoch);
  test_difftime(&epoch);
  test_mktime(&epoch);

	return 0;
}
