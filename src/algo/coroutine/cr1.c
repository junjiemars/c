#include "_algo_.h"

/*
 *
 * https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html
 * https://www.chiark.greenend.org.uk/~sgtatham/coroutine.h
 * https://www.ibm.com/docs/en/aix/7.1?topic=programming-writing-reentrant-threadsafe-code
 *
 */


static int   range1(int, int);
static int   range2(int, int);
static void  test(int (*)(int, int), int, int);


struct ccr_ctx_s
{
  int val;
  int state;
};


static int   range3_r(int, int, struct ccr_ctx_s*);
static void  test_r(int (*)(int, int, struct ccr_ctx_s*), int, int);



int
main(void)
{
  test(range1, 1, 5);
  test(range2, 1, 5);
  test_r(range3_r, 1, 5);

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
  state = 0;

  return -1;
}


#define _scr_begin_  static int state = 0; switch(state) { case 0:
#define _scr_return_(x)                                          \
do { state = __LINE__; return (x); case __LINE__:; } while (0)
#define _scr_finish_(z)  } state = 0; return (z)

int
range2(int a, int b)
{
  static int  i;

  _scr_begin_;

  for (i = a; i < b; i++)
    {
      _scr_return_(i);
    }

  _scr_finish_(-1);
}

void
test_r(int (*fn)(int, int, struct ccr_ctx_s*), int a, int b)
{
  struct ccr_ctx_s  *ctx;

  ctx = malloc(sizeof(*ctx));
  ctx->state = 0;

  for (int i; (i = fn(a, b, ctx)) != -1;)
    {
      printf("%d\n", i);
    }

  free(ctx);
}

#define _ccr_begin_(ctx)  switch(ctx->state) { case 0:
#define _ccr_set_(ctx, x)  ctx->val = (x)
#define _ccr_get_(ctx)  ctx->val
#define _ccr_inc_(ctx)  ctx->val += 1
#define _ccr_return_(ctx)                                               \
do { ctx->state = __LINE__; return (ctx->val); case __LINE__:; } while (0)
#define _ccr_finish_(ctx, z)  } ctx->state = 0; return (z)

int
range3_r(int a, int b, struct ccr_ctx_s *ctx)
{
  _ccr_begin_(ctx);

  for (_ccr_set_(ctx, a); _ccr_get_(ctx) < b; _ccr_inc_(ctx))
    {
      _ccr_return_(ctx);
    }

  _ccr_finish_(ctx, -1);
}
