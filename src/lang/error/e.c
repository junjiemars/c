#include <_lang_.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

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

int
main(int argc, char **argv) {
  if (argc < 2) {
    printf("input a filename\n");
    return 0;
  }

  test_open_file(argv[1]);

  return 0;
}
