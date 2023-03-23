#include "d.h"
#include <stdio.h>
#include <stdlib.h>


int
main(int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <integers...>\n");
      return 1;
    }

  int nums_size = argc - 1;
  int *nums = calloc(nums_size, sizeof(int));

  for (int i = 1; i < argc - 1; i++)
    {
      nums[i] = atoi(argv[i]);
    }

  int return_size = 0;
  int *return_col_size = 0;

  int **ns = sum3(nums, nums_size, &return_size, &return_col_size);

  for (int i = 0; i < return_size; i++)
    {
      printf("[");

      for (int j = 0; j < *return_col_size; j++)
        {
          printf("%d,", ns[i][j]);
        }

      printf("]\n");
    }

  return 0;
}
