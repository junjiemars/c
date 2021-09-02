#include <_algo_.h>
#include <permute/permute.h>


int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

	int a1[] =
    {
      0x3, 0x5, 0x1, 0x4, 0x1, 0x2
    };
  size_t p1[] =
    {
      3, 2, 0
    };
  
  printf("permutation:\n----------\n");
	list_array(p1, count(p1), sizeof(*p1), print_size_t);
	printf("permute+:\n----------\n");
	list_array(a1, count(a1), sizeof(*a1), print_int);
	printf("permute-:\n----------\n");
	permute(a1, count(a1), sizeof(*a1), p1, count(p1), cmp_int);
	list_array(a1, count(a1), sizeof(*a1), print_int);

	/* char *s1[] = */
  /*   { */
  /*     "block", "array", "floor", "digit", "floor", "cell", "cell" */
  /*   }; */
	/* printf("sort+:\n----------\n"); */
	/* list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str); */
	/* printf("sort-:\n----------\n"); */
	/* sort(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), cmp_str); */
	/* list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str); */

  return 0;
}
