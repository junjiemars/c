#include "_process_.h"
#include <sys/times.h>

#define clk_diff(a, b)  ((a) - (b)) / (double) NM_CLK_TCK
#define time_diff(a, b)  ((a) - (b)) / (double) NM_CLK_TCK

static char  cmd[NM_LINE_MAX];



int
main(int argc, char **argv)
{
  int         rc;
  clock_t     s_clk, e_clk;
  struct tms  s_tms, e_tms;

  for (int i = 1; i < argc; i++)
    {
      strcat(cmd, " ");
      strcat(cmd, argv[i]);
    }

  s_clk = times(&s_tms);

  if ((rc = system(cmd)) < 0)
    {
      perror(NULL);
    }

  e_clk = times(&e_tms);

  printf("real: %7.2f\n", clk_diff(e_clk, s_clk));
  printf("user: %7.2f\n", time_diff(e_tms.tms_utime, s_tms.tms_utime));
  printf("sys:  %7.2f\n", time_diff(e_tms.tms_stime, s_tms.tms_stime));

  exit(EXIT_SUCCESS);
}
