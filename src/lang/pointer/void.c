#include "_lang_.h"

/*
 * `void*' runtime generic
 *
 */

static int  qsort_str_cmp(const void*, const void*);
static int  qsort_int_cmp(const void*, const void*);
static int  qsort_blk_str_cmp(const void*, const void*);
static int  qsort_blk_int_cmp(const void*, const void*);

static void test_sort_strs();
static void test_sort_ints();
static void test_sort_blks();

struct block_s
{
  int    num;
  char  *name;
};


int
main(void)
{
  test_sort_strs();
  test_sort_ints();
  test_sort_blks();

  return 0;
}

void
test_sort_strs()
{
  printf("sort strings\n----------\n");

	char*  ss1[]  =  { "a", "orange", "apple", "berry", 0, };

  for (char **p = ss1; *p != 0; p++)
    {
      printf("%s ", p[0]);
    }
  putchar('\n');

	qsort(ss1, sizeof(ss1)/sizeof(*ss1)-1, sizeof(*ss1), qsort_str_cmp);

	for (char **p = ss1; *p != 0; p++)
    {
      printf("%s ", p[0]);
    }
	putchar('\n');

}

void
test_sort_ints()
{
  printf("sort integers\n------------\n");

	int  ns1[10];

	srand((unsigned) time(0));

	for (int i = 0; i < (int) (sizeof(ns1)/sizeof(*ns1)); i++)
    {
      ns1[i] = rand() % 100;
      printf("%d ", ns1[i]);
    }
	putchar('\n');

	qsort(ns1, sizeof(ns1)/sizeof(*ns1), sizeof(*ns1), qsort_int_cmp);
	for (int i = 0; i < (int) (sizeof(ns1)/sizeof(*ns1)); i++)
    {
      printf("%d ", ns1[i]);
    }
	putchar('\n');
}

void
test_sort_blks()
{
	printf("sort blocks\n----------\n");

  struct block_s  blks[] =
    {
      {.name = "a"}, {.name = "berry"}, {.name = "apple"}, {.name = "orange"}
    };

  srand((unsigned) time(0));

  for (int i = 0; i < (int) (sizeof(blks)/sizeof(*blks)); i++)
    {
      blks[i].num = rand() % 10;
      printf("{ num = %d, name = \"%s\" }\n", blks[i].num, blks[i].name);
    }

  printf("block_s.name:\n");

  qsort(blks, sizeof(blks)/sizeof(*blks), sizeof(*blks), qsort_blk_str_cmp);

  for (int i = 0; i < (int) (sizeof(blks)/sizeof(*blks)); i++)
    {
      printf("{ num = %d, name = \"%s\" }\n", blks[i].num, blks[i].name);
    }

  printf("block_s.num:\n");

  qsort(blks, sizeof(blks)/sizeof(*blks), sizeof(*blks), qsort_blk_int_cmp);

  for (int i = 0; i < (int) (sizeof(blks)/sizeof(*blks)); i++)
    {
      printf("{ num = %d, name = \"%s\" }\n", blks[i].num, blks[i].name);
    }
  putchar('\n');
}

int
qsort_str_cmp(const void *x, const void *y)
{
	const char *l = *(const char**) x;
	const char *r = *(const char**) y;
	return strcmp(l, r);
}

int
qsort_int_cmp(const void *x, const void *y)
{
	const int  l  =  *(const int*) x;
	const int  r  =  *(const int*) y;
	if (l < r) return -1;
	if (l > r) return 1;
	return 0;
}

int
qsort_blk_str_cmp(const void *x, const void *y)
{
  return qsort_str_cmp(&((const struct block_s*) x)->name,
                       &((const struct block_s*) y)->name);
}

int
qsort_blk_int_cmp(const void *x, const void *y)
{
  return qsort_int_cmp(&((const struct block_s*) x)->num,
                       &((const struct block_s*) y)->num);
}
