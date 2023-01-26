#include "_algo_.h"

/*
 *
 * https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
 * https://www.chiark.greenend.org.uk/~sgtatham/coroutine.h
 *
 */

static int  range1(int, int);
static int  range2(int, int);


static void  test(int (*)(int, int), int, int);


int
main(void)
{
  test(range1, 1, 5);
  test(range2, 1, 5);

  return 0;
}

void
test(int (*fn)(int, int), int a, int b)
{
  int i;

  for (; (i = fn(a, b)) != -1;)
    {
      printf("%d\n", i);
    }
}

int
range1(int a, int b)
{
  static int  i      =  0;
  static int  state  =  0;

  switch (state)
    {
    case 0:
      state = 1;
      for (i = a; i < b; i++)
        {
          return i;
        case 1:
          ;
        }
    }

  return -1;
}


#define _cr_begin_  static int state=0; switch(state) { case 0:
#define _cr_return_(x)                                          \
do { state = __LINE__; return (x); case __LINE__:; } while (0)
#define _cr_finish_(z)  } return (z)

int
range2(int a, int b)
{
  static int  i;

  _cr_begin_;

  for (i = a; i < b; i++)
    {
      _cr_return_(i);
    }

  _cr_finish_(-1);
}
