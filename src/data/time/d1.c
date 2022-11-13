#include "_data_.h"
#include <time.h>


/*
 * Emulates the default behavior of date(1).
 *
 */

static char  buf[NM_LINE_MAX];


int
main(void)
{
  time_t      cal;
  struct tm  *loc;

  if ((cal = time(NULL)) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if ((loc = localtime(&cal)) == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (strftime(buf, NM_LINE_MAX, "%a %b %d %X %Z %Y\n", loc) == 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fputs(buf, stdout);

  exit(EXIT_SUCCESS);
}
