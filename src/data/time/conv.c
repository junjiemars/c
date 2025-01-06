#include "../_data_.h"
#include <sys/time.h>
#include <time.h>

void pr_time_t (const char *, const time_t *);
void pr_tm (const char *, const struct tm *);
void pr_str (const char *, const char *);

int
main (void)
{
  char *s;
  char buf[64];
  time_t tt_utc, tt_loc;
  struct tm *bt_loc, *bt_gmt;

  /* get time_t of UTC */
  tt_utc = time (NULL);
  pr_time_t ("time", &tt_utc);

  /* localtime: time_t -> tm (broken-down time)  */
  bt_loc = localtime (&tt_utc);
  pr_tm ("localtime", bt_loc);

  /* gmtime: time_t -> tm (UTC) */
  bt_gmt = gmtime (&tt_utc);
  pr_tm ("gmtime", bt_gmt);

  /* ctime: time_t -> string */
  s = ctime (&tt_utc);
  pr_str ("ctime", s);

  /* mktime: tm (local time) -> time_t */
  tt_loc = mktime (bt_loc);
  pr_time_t ("mktime", &tt_loc);
  assert (tt_utc == tt_loc);

  /* asctime: tm -> string */
  s = asctime (bt_loc);
  pr_str ("asctime (loc)", s);
  s = asctime (bt_gmt);
  pr_str ("asctime (gmt)", s);

  /* format */
  strftime (buf, sizeof (buf), "%c", bt_loc);
  pr_str ("strftime", buf);

  /* time zone */
  /* tzset(); */

  putchar ('\n');

  exit (EXIT_SUCCESS);
}

void
pr_time_t (const char *h, const time_t *t)
{
  printf ("\n%s:\n------------\n%ld\n", h, *t);
}

void
pr_tm (const char *h, const struct tm *bt)
{
  printf ("\n%s:\n------------\n"
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
pr_str (const char *h, const char *s)
{
  printf ("\n%s:\n------------\n%s", h, s);
}
