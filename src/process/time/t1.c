#include "_process_.h"
#include <sys/times.h>

int
main(void)
{
  clock_t     rc;
  struct tms  buf;

  rc = times(&buf);
  if ((clock_t) -1 == rc)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("struct tms {\n"
         "  tms_utime: %ld,\n"
         "  tms_stime: %ld,\n"
         "}\n"
         "wall clock time: %ld",
         buf.tms_utime, buf.tms_stime, rc);

  exit(EXIT_SUCCESS);
}
