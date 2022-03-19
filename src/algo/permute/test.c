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
      3, 2, 2, 3, 4, 5
    };

  printf("permutation:\n----------\n");
	list_array(p1, _nof_(p1), sizeof(*p1), print_size_t);
	printf("permute+:\n----------\n");
	list_array(a1, _nof_(a1), sizeof(*a1), print_int);
	printf("permute-:\n----------\n");
	permute(a1, _nof_(a1), sizeof(*a1), p1, cmp_int);
	list_array(a1, _nof_(a1), sizeof(*a1), print_int);

	char *s1[] =
    {
      "block", "array", "floor", "digit", "cell", "error"
    };
  printf("permutation:\n----------\n");
	list_array(p1, _nof_(p1), sizeof(*p1), print_size_t);
	printf("permute+:\n----------\n");
	list_array(s1, _nof_(s1), sizeof(*s1), print_str);
	printf("permute-:\n----------\n");
	permute(s1, _nof_(s1), sizeof(*s1), p1, cmp_str);
	list_array(s1, _nof_(s1), sizeof(*s1), print_str);

  const int ss_len = _nof_(p1);
  struct score_s *ss = malloc(sizeof(struct score_s) * ss_len);
  if (!ss)
    {
      return 1;
    }
  for (int i = 0; i< ss_len; i++)
    {
      char c = ('a' + (char) i);
      sprintf(ss[i].name, "%c%c%c", c, c, c);
      ss[i].score = 10 + i * 10;
    }
  printf("permutation:\n----------\n");
	list_array(p1, _nof_(p1), sizeof(*p1), print_size_t);
	printf("permute+:\n----------\n");
	list_array(ss, ss_len, sizeof(*ss), print_score_s);
	printf("permute-:\n----------\n");
	permute(ss, ss_len, sizeof(*ss), p1, cmp_score_s);
	list_array(ss, ss_len, sizeof(*ss), print_score_s);

  free(ss);

  return 0;
}
