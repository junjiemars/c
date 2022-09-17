#include "_process_.h"
#include <sys/times.h>

/*
 * simulate time(1)
 *
 */



#define clk_diff(a, b)  ((a) - (b)) / (double) NM_CLK_TCK
#define time_diff(a, b)  ((a) - (b)) / (double) NM_CLK_TCK

static char  cmd[NM_LINE_MAX];



int
main(int argc, char **argv)
{
  int         rc;
  clock_t     b_clk  =  0, e_clk = 0;
  struct tms  b_tms  =  {0}, e_tms = {0};

  for (int i = 1; i < argc; i++)
    {
      strcat(cmd, " ");
      strcat(cmd, argv[i]);
    }


  b_clk = times(&b_tms);
  if ((rc = system(cmd)) < 0)
    {
      perror(NULL);
    }
  e_clk = times(&e_tms);


  fprintf(stderr, "real: %7.2f\n", clk_diff(e_clk, b_clk));
  fprintf(stderr, "user: %7.2f\n",
          time_diff(e_tms.tms_utime, b_tms.tms_utime));
  fprintf(stderr, "sys:  %7.2f\n",
          time_diff(e_tms.tms_stime, b_tms.tms_stime));

  exit(EXIT_SUCCESS);
}
