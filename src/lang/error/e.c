#include <_lang_.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

int
main(int argc, char **argv) {
  if (argc < 2) {
    printf("input a filename\n");
    return 0;
  }

  FILE* out = 0;
  out = fopen(argv[1], "r");
  if (0 == out) {
    int e = errno;
  	if (e) {
      perror(argv[1]);
      fprintf(stderr, "#open %s failed, caused by: %s\n",
              argv[1], strerror(e));
      
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

  return 0;
}
