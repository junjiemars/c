#include "_data_.h"
#include <time.h>
#include <sys/time.h>


void pr_time_t(const char *, const time_t *);
void pr_tm(const char *, const struct tm *);
void pr_str(const char *, const char *);

int
main(void)
{
  char       *s;
  time_t      t;
  struct tm  *bt;


  /* get time_t of UTC */
  t = time(NULL);
  pr_time_t("time", &t);


  /* localtime: time_t -> tm (broken-down time)  */
  bt = localtime(&t);
  pr_tm("localtime", bt);


  /* gmtime: time_t -> tm (UTC) */
  bt = gmtime(&t);
  pr_tm("gmtime", bt);


  /* ctime: time_t -> string */
  s = ctime(&t);
  pr_str("ctime", s);


  /* mktime: tm -> time_t */
  t = mktime(bt);
  pr_time_t("mktime", &t);


  /* asctime: tm -> string */
  s = asctime(bt);
  pr_str("asctime", s);


  exit(EXIT_SUCCESS);
}


void
pr_time_t(const char *h, const time_t *t)
{
  printf("\n%s:\n------------\n%ld\n", h, *t);
}

void
pr_tm(const char *h, const struct tm *bt)
{
  printf("\n%s:\n------------\n"
         "tm_sec: %i\n"
         "tm_min: %i\n"
         "tm_hour: %i\n"
         "tm_mday: %i\n"
         "tm_mon: %i\n"
         "tm_year: %i\n"
         "tm_wday: %i\n"
         "tm_yday: %i\n"
         "tm_isdst: %i\n",
         h, bt->tm_sec, bt->tm_min, bt->tm_hour, bt->tm_mday, bt->tm_mon,
         bt->tm_year, bt->tm_wday, bt->tm_yday, bt->tm_isdst);
}

void
pr_str(const char *h, const char *s)
{
  printf("\n%s:\n------------\n%s", h, s);
}
