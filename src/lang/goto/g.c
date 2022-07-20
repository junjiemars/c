#include <_lang_.h>

/*
 * 1) goto idiom for cleanning up;
 * 2) use longjmp jump to other function;
 */

#if MSVC
#pragma warning(disable:4267) /* conversion possible loss of data */
#endif


static int sum(int*, size_t);
static void loop(void);


int
main(void)
{
	size_t size = 10;
	int *v = (int*)malloc(sizeof(int) * size);
	for (size_t i = 0; i < size; i++)
    {
      v[i] = i;
    }
	v[6] = -1;

	printf("# using goto to clean up ... ");
	printf("sum of v[] is %i\n", sum(v, size));

	printf("# using goto do a loop ... ");
	loop();
}

int
sum(int *v, size_t size)
{
  int c = 0;

  for (size_t i = 0; i < size; i++)
    {
      if (v[i] < 0) goto clean_exit;
      c += v[i];
    }

 clean_exit:
  free(v);
  return c;
}

void
loop(void)
{
  int a[] =
    {0, 1, 2, 3, 4, 5};
  int i = 0;

 begin:
  if (a[i] >= 3)
    {
      printf(">=%d ", i);
      goto end;
    }
  i = i+1;
  goto begin;
 end:
  printf("goto :end label\n");
}
