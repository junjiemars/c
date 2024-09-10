#include "_process_.h"

static void on_exit1 (void);
static void on_exit2 (void);

int
main (void)
{
  atexit (on_exit2);
  atexit (on_exit1);
  atexit (on_exit1);
}

void
on_exit1 (void)
{
  static int i = 0;
  printf ("%d. first exit\n", i++);
}

void
on_exit2 (void)
{
  printf ("second exit\n");
}
