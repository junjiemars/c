#include "_process_.h"

/*
 * simulate time(1)
 *
 */

#define clk_real(a) ((a) / (double)NM_CLK_TCK)
#define time_diff(a, b) (((a) - (b)) / (double)NM_CLK_TCK)

static void do_cmd (const char *);
static void pr_times (clock_t, struct tms *, struct tms *);

int
main (int argc, char **argv)
{
  for (int i = 1; i < argc; i++)
    {
      do_cmd (argv[i]);
    }

  exit (EXIT_SUCCESS);
}

void
do_cmd (const char *cmd)
{
  int rc;
  clock_t b_clk = 0, e_clk = 0;
  struct tms b_tms = { 0 }, e_tms = { 0 };

  b_clk = times (&b_tms);
  if ((rc = system (cmd)) < 0)
    {
      perror (NULL);
      return;
    }
  e_clk = times (&e_tms);

  pr_times (e_clk - b_clk, &b_tms, &e_tms);
}

void
pr_times (clock_t real, struct tms *start, struct tms *end)
{
  fprintf (stderr, "real: %7.2f\n", clk_real (real));
  fprintf (stderr, "user: %7.2f\n",
           time_diff (end->tms_utime, start->tms_utime));
  fprintf (stderr, "sys:  %7.2f\n",
           time_diff (end->tms_stime, start->tms_stime));
  fprintf (stderr, "child user: %7.2f\n",
           time_diff (end->tms_cutime, start->tms_cutime));
  fprintf (stderr, "child sys: %7.2f\n",
           time_diff (end->tms_cstime, start->tms_cstime));
}
