#include "d.h"

int **
sum3(int *nums, int nums_size, int *return_size, int **return_col_size)
{
  if (nums == 0 || nums_size == 0)
    {
      *return_size = 0;
      *return_col_size = 0;
      return (int**) 0;
    }

  int **rs = 0;
  int *cs = 0;
  int **ptr_rs = 0;
  int *ptr_cs = 0;
  size_t rs_size = 4;

  rs = malloc(sizeof(int*) * rs_size);
  cs = malloc(sizeof(int) * rs_size);

  ptr_rs = rs;
  ptr_cs = cs;

  for (int i = 0; i < nums_size; i++)
    {
      if ((size_t) *return_size == rs_size)
        {
          ptrdiff_t offset = ptr_rs - rs;
          rs_size *= 2;
          rs = realloc(rs, rs_size);
          ptr_rs = rs + offset;
          cs = realloc(cs, rs_size);
          ptr_cs = cs + offset;
        }

      for (int j = i+1; j < nums_size; j++)
        {
          for (int k = j+1; k < nums_size; k++)
            {
              if (nums[i] + nums[j] + nums[k] == 0)
                {
                  int *r = malloc(sizeof(int) * 3);

                  r[0] = nums[i];
                  r[1] = nums[j];
                  r[2] = nums[k];

                  *ptr_rs = r;

                  ptr_cs[0] = 3;

                  ptr_rs++;
                  ptr_cs++;
                  *return_size += 1;
                }
            }
        }
    }

  *return_col_size = cs;

  return rs;
}
