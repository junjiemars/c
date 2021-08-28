#include <_algo_.h>
#include <sort/sort.h>


int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

	int a1[] =
    {
      0x3, 0x5, 0x1, 0x4, 0x1, 0x2
    };
	printf("sort+:\n----------\n");
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);
	printf("sort-:\n----------\n");
	sort(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), cmp_int);
	list_array(a1, sizeof(a1)/sizeof(*a1), sizeof(*a1), print_int);

	char *s1[] =
    {
      "block", "array", "floor", "digit", "floor", "cell", "cell"
    };
	printf("sort+:\n----------\n");
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);
	printf("sort-:\n----------\n");
	sort(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), cmp_str);
	list_array(s1, sizeof(s1)/sizeof(*s1), sizeof(*s1), print_str);

  return 0;
}
