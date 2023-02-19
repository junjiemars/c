#include "_algo_.h"

/*
 * https://inst.eecs.berkeley.edu/~cs61c/sp06/handout/fixedpt.html
 *
 */


typedef struct real_s
{
#if (NM_HAVE_LITTLE_ENDIAN)
  unsigned int val : 28;
  unsigned int fix : 4;
#else
  unsigned int fix : 4;
  unsigned int val : 28;
#endif
} real_t;


real_t   real_from_int(int);
int      real_to_int(real_t);
int      real_eq(real_t, real_t);
real_t   real_add(real_t, real_t);
real_t   real_mul(real_t, real_t);
real_t   real_div(real_t, real_t);
char    *rtos(const real_t*, char*, size_t);


int
main(void)
{
  real_t r53 = real_from_int(53);
  assert(real_eq(r53, real_from_int(53)));

  real_t r54 = real_from_int(53+1);
  assert(real_eq((real_add(r53, real_from_int(1))), r54));

  real_t r2 = real_from_int(2);
  real_t r26 = real_from_int(26);
  real_t r52 = real_from_int(52);
  real_t q26 = real_div(r53, r2);

  assert(real_eq(r52, real_mul(r26, r2)));
  assert(real_eq(r53, real_mul(q26, r2)));

  char ss[16];
  printf("%s\n", rtos(&q26, ss, _nof_(ss)));

  /* real_t r3 = real_from_int(3); */
  /* real_t q17 = real_div(r53, r3); */
  /* printf("%s\n", rtos(&q17, ss, _nof_(ss))); */

  return 0;
}


char*
rtos(const real_t *r, char *str, size_t size)
{
  int                  i;
  unsigned int         x = 0, y;
  static unsigned int  fix[]  =  { 0625, 1250, 2500, 5000 };


  for (y = r->fix, i = 0; y; y >>= 1, i++)
    {
      if (r->fix & (1 << i))
        {
          x += fix[i];
        }
    }
  snprintf(str, size, "%u.%u", r->val, x);

  return str;
}


real_t
real_from_int(int a)
{
  unsigned int  i  =  a << 4;
  real_t        r  =  *(real_t*)(unsigned int*) &i;
  return r;
}

int
real_to_int(real_t r)
{
  unsigned int  i  =  *(unsigned int*)((real_t*) &r);
  return i >> 4;
}

int
real_eq(real_t a, real_t b)
{
  return *(unsigned int*)((real_t*) &a) == *(unsigned int*)((real_t*) &b);
}

real_t
real_add(real_t a, real_t b)
{
  unsigned int x  =  *(unsigned int*)((real_t*) &a)
    + *(unsigned int*)((real_t*) &b);
  return *(real_t*) &x;
}

real_t
real_mul(real_t a, real_t b)
{
  unsigned int  r  =  *(unsigned int*)((real_t*) &a)
    * *(unsigned int*)((real_t*) &b);
  return real_from_int(r >> 8);
}

real_t
real_div(real_t a, real_t b)
{
  unsigned int  x;
  unsigned int  r  =  *(unsigned int*)((real_t*) &a);

  for (x = b.val >> 1; x; x >>= 1)
    {
      r >>= 1;
    }
  for (x = b.fix >> 1; x; x >>= 1)
    {
      r <<= 1;
    }
  return *(real_t*)((int*) &r);
}
