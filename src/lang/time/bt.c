#include "../_lang_.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

/* #if !defined(__USE_MISC) */
/* #define __USE_MISC */
/* #endif */

#if (MSVC)
#define timegm _mkgmtime
#endif /* end of MSVC */

#include <time.h>

/*
 * time_t -> struct tm -> char*
 */

void test_epoch (time_t *);
void test_localtime (const time_t *);

#if !(MSVC)
void test_timelocal (const time_t *);
#endif /* end of !MSVC */

void test_gmtime (const time_t *);
void test_ctime (const time_t *);
void test_difftime (const time_t *);
void test_mktime (const time_t *);

void
test_epoch (time_t *epoch)
{
  if ((time_t)-1 == time (epoch))
    {
      perror (0);
      return;
    }
  printf ("epoch since 1/1/1970 UTC: %zu\n", *epoch);
}

void
test_localtime (const time_t *epoch)
{
  __attribute__ ((unused)) struct tm *local = localtime (epoch);
}

#if !(MSVC)
void
test_timelocal (__attribute__ ((unused)) const time_t *epoch)
{
  /* struct tm *local = localtime(epoch); */
  /* time_t lacol = timelocal(local); */
  /* assert(*epoch == lacol && "localtime <=> timelocal"); */
  /* char *asc = asctime(local); */
  /* printf("asctime of localtime: %s", asc); */
}
#endif /* end of !MSVC */

void
test_gmtime (__attribute__ ((unused)) const time_t *epoch)
{
  /* struct tm *gm = gmtime(epoch); */
  /* time_t mg = timegm(gm); */
  /* assert(*epoch == mg); */
  /* char *asc = asctime(gm); */
  /* printf("asctime of gmtime: %s", asc); */
}

void
test_ctime (const time_t *epoch)
{
  char *c = ctime (epoch);
  char *c1 = asctime (localtime (epoch));
  assert (0 == strcmp (c, c1));
  printf ("ctime of epoch: %s", c);
}

void
test_difftime (const time_t *epoch)
{
  time_t end = (time_t)(*epoch + 60 * 60 * 24);
  double d = difftime (end, *epoch);
  printf ("difftime(%zu, %zu) in seconds = %lf\n", end, *epoch, d);
}

void
test_mktime (const time_t *epoch)
{
  struct tm *local = gmtime (epoch);
  local->tm_year++;
  char *asc = asctime (local);
  printf ("asctime of localtime: %s", asc);
}

int
main (void)
{
  time_t epoch = 0;

  test_epoch (&epoch);

  test_localtime (&epoch);

#if !(MSVC)
  test_timelocal (&epoch);
#endif /* end of !MSVC */

  test_gmtime (&epoch);
  test_ctime (&epoch);
  test_difftime (&epoch);
  test_mktime (&epoch);

  return 0;
}
