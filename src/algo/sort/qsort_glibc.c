#include <_algo_.h>
#include "sort.h"

#define MAX_THRESH  4
#define STACK_SIZE	(sizeof(size_t) *  8)

#ifdef stack_push
#  undef stack_push
#endif
#define stack_push(low, high)	 ((void) ((top->lo = (low)), (top->hi = (high)), ++top))

#ifdef stack_pop
#  undef stack_pop
#endif
#define	stack_pop(low, high)	((void) (--top, (low = top->lo), (high = top->hi)))

#ifdef stack_not_empty
#  undef stack_not_empty
#endif
#define	stack_not_empty()  (stack < top)


typedef struct
{
  char *lo;
  char *hi;
} stack_node_s;


void
sort(void *base, size_t n, size_t width,
     int (*cmp)(const void *, const void *))
{
  char          *b;
  const size_t   max_thresh  =  width * MAX_THRESH;;

  if (n < 2)
    {
      return;
    }

  b = (char *) base;

  if (n == 0)
    {
      return;
    }

  if (n > MAX_THRESH)
    {
      char          *lo   =  b;
      char          *hi   =  &lo[width * (n - 1)];
      stack_node_s   stack[STACK_SIZE];
      stack_node_s  *top  =  stack;

      stack_push(NULL, NULL);

      while (stack_not_empty())
        {
          char *left;
          char *right;
          char *mid = lo + width * ((hi - lo) / width >> 1);

          if (cmp(mid, lo) < 0)
            {
              swap(mid, lo, width);
            }
          if (cmp(hi, mid) < 0)
            {
              swap(mid, hi, width);
            }
          else
            {
              goto jump_over;
            }
          if (cmp(mid, lo) < 0)
            {
              swap(mid, lo, width);
            }
        jump_over:;

          left  = lo + width;
          right = hi - width;

          do
            {
              while (cmp(left, mid) < 0)
                {
                  left += width;
                }

              while (cmp(mid, right) < 0)
                {
                  right -= width;
                }

              if (left < right)
                {
                  swap(left, right, width);
                  if (mid == left)
                    {
                      mid = right;
                    }
                  else if (mid == right)
                    {
                      mid = left;
                    }
                  left += width;
                  right -= width;
                }
              else if (left == right)
                {
                  left += width;
                  right -= width;
                  break;
                }
            } while (left <= right);

          if ((size_t) (right - lo) <= max_thresh)
            {
              if ((size_t) (hi - left) <= max_thresh)
                {
                  stack_pop(lo, hi);
                }
              else
                {
                  lo = left;
                }
            }
          else if ((size_t) (hi - left) <= max_thresh)
            {
              hi = right;
            }
          else if ((right - lo) > (hi - left))
            {
              stack_push(lo, right);
              lo = left;
            }
          else
            {
              stack_push(left, hi);
              hi = right;
            }
        }
    }

  {
    char *const   end     =  &b[width * (n - 1)];
    char         *tmp     =  b;
    char         *thresh  =  _min_(end, b + max_thresh);
    char         *run;

    for (run = tmp + width; run <= thresh; run += width)
      {
        if (cmp(run, tmp) < 0)
          {
            tmp = run;
          }
      }

    if (tmp != b)
      {
        swap(tmp, b, width);
      }

    run = b + width;
    while ((run += width) <= end)
      {
        tmp = run - width;
        while (cmp(run, tmp) < 0)
          {
            tmp -= width;
          }

        tmp += width;
        if (tmp != run)
          {
            char  *trav;

            trav = run + width;
            while (--trav >= run)
              {
                char c = *trav;
                char *hi, *lo;

                for (hi = lo = trav; (lo -= width) >= tmp; hi = lo)
                  {
                    *hi = *lo;
                  }
                *hi = c;
              }
          }
      }
  }
}
