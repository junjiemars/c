#include <_lang_.h>
#include <string.h>
#include <stdio.h>


#if MSVC
/* warning C4996: 'strtok': This function or variable may be
	 unsafe. Consider using strtok_s instead. To disable deprecation,
	 use _CRT_SECURE_NO_WARNINGS */
#  pragma warning(disable : 4996)
#endif

static void
test_strchr(char *ss, int c) {
  char *s1 = strchr(ss, c);
  if (s1) {
    fprintf(stdout, "%s\n", s1);
  } else {
    fprintf(stdout, "no found\n");
  }
}

static void
test_strrchr(char *ss, int c) {
  char *s1 = strrchr(ss, c);
  if (s1) {
    fprintf(stdout, "%s\n", s1);
  } else {
    fprintf(stdout, "no found\n");
  }
}

int
main(int argc, char **argv) {
	if (argc < 2) {
		printf("what string and found what\n");
		return 0;
	}

  char *ss = argv[1];
  int c = argv[2][0];
  
  test_strchr(ss, c);
  test_strrchr(ss, c);
  
  return 0;
}
