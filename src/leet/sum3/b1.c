#include "d.h"

int **
sum3(int *nums, int nums_size, int *return_size, int **return_col_size)
{
  if (nums == 0 || nums_size)
    {
      *return_size = 0;
      *return_col_size = 0;
      return 0;
    }

  int **ns = 0;
  int **ptr_ns = ns;

  for (int i = 0; i < nums_size; i++)
    {
      for (int j = i+1; j < nums_size; j++)
        {
          for (int k = j+1; k < nums_size; k++)
            {
              if (nums[i] + nums[j] + nums[k] == 0)
                {
                  *ptr_ns = malloc(sizeof(int) * 3);
                  *ptr_ns[0] = nums[i];
                  *ptr_ns[1] = nums[j];
                  *ptr_ns[2] = nums[k];
                  ptr_ns++;
                }
            }
        }
    }

  *return_size = 1;

  *ns = malloc(sizeof(int) * *return_size);
  *return_col_size = malloc(sizeof(int));

  *return_col_size[0] = 1;

  return ns;
}
