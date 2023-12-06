#include <_lang_.h>

static int n;
static volatile int n1;

static void bar (void);
static void bar1 (void);
static int incr (void);

int
main (void)
{
  bar ();
  bar1 ();
  incr ();

  return 0;
}

void
bar (void)
{
  /* with clang -O2 optimized will keep function skeleton, just
     like:
     void bar(void)
     {}
     because n has ever changed
  */
  n = 0;
  int i = 0;
  while (n != 254)
    {
      if (++i > 3)
        {
          break;
        }
    }
}

void
bar1 (void)
{
  /*
   * With -O2/-O2:
   * 1. bar1 may be inline into main routine
   * 2. but, load n1 from memory never disappear
   */
  n1 = 0;
  int i = 0;
  while (n1 != 255)
    {
      if (++i > 3)
        {
          break;
        }
    }
}

int
incr (void)
{
  /*
   * Always:
   * 1. load from memory
   * 2. add
   * 3. store back to memory
   */
  n1 += 0xff;
  return n1;
}
