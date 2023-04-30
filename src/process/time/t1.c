#include "_process_.h"


int
main(void)
{
  clock_t     rc;
  struct tms  buf;

  if ((rc = times(&buf)) == (clock_t) -1)
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
