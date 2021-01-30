#include "_lang_.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

#if (LINUX)
#  if defined(_GNU_SOURCE)
#    undef _GNU_SOURCE
#  endif  /* _GNU_SOURCE */
#  include <errno.h>
#else
#  include <errno.h>
#endif  /* LINUX */

void
test_open_file(const char *filename) {
  FILE *out = fopen(filename, "r");
  if (0 == out) {
    int e = errno;
  	if (e) {
      perror(filename);
      fprintf(stderr, "#open %s failed, caused by: %s\n",
              filename, strerror(e));
      
      char buf[512];
      int r = strerror_r(e, buf, sizeof(buf));
      if (0 == r) {
        fprintf(stderr, "#r\"%s\"\n", buf);
      } else {
        fprintf(stderr, "#strerror_r failed: %s\n", strerror(r));
      }
  	}
  }

  if (out) {
    fclose(out);
  }
}

void
test_sqrt(double x) {
  double d = sqrt(x);
  printf("%f\n", d);
}

int
main(int argc, char **argv) {
  if (argc < 2) {
    printf("input a filename\n");
    return 0;
  }

  test_open_file(argv[1]);
  test_sqrt(-1 * argc);

  return 0;
}
