#include "../_lang_.h"
#include <setjmp.h>
#include <stdio.h>

/*
 * 1. demonstrates the basis usage of `setjmp' and `longjmp'.
 *
 * 2. signal processing discussed in src/signal.
 *
 */

static jmp_buf env;
static volatile int flag = 0x11223344;

static void a (void);
static void b (volatile int *);
static void c (volatile int *);

int
main (void)
{
  a ();
}

void
a (void)
{
  int val;
  volatile int flag_in_stack = flag;

  printf ("> setjmp()\n[flag=0x%x, flag_in_stack=0x%x]\n=> ", flag,
          flag_in_stack);

  if (0 != (val = setjmp (env)))
    {
      printf ("\n< longjmp(0x%x)\n[flag=0x%x, flag_in_stack=0x%x]\n", val,
              flag, flag_in_stack);
    }
  else
    {
      printf ("b() => ");
      b (&flag_in_stack);
    }
}

void
b (volatile int *flag_in_stack)
{
  printf ("c() => ");
  c (flag_in_stack);
}

void
c (volatile int *flag_in_stack)
{
  flag = 0x44332211;
  *flag_in_stack = flag;
  printf ("longjmp() => ");
  longjmp (env, 0x1234);
}
