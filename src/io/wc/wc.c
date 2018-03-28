#include <_io_.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>

void
usage() {
  printf("usage: wc [-cl] [file ...]\n");
}

errno_t
count_bytes(char const* name, size_t *count) {
	FILE* file = fopen(name, "rb");
	errno_t err = errno;
	if (err) {
		return err;
	}

	// todo:
	
 clean:
	if (file) {
		close(file);
	}

	return err;
}

int 
main(int argc, char **argv) {
  int opt_count_bytes = 1;
  int opt_count_lines = 1;
  char *opt_filename = 0;

  int ch;
  while (-1 != (ch = getopt(argc, argv, "cl"))) {
    switch (ch) {
      case 'c':
        opt_count_bytes = 1;
        break;
      case 'l':
        opt_count_lines = 1;
        break;
      default:
        if ('-' == optarg[0]) {
          printf("%s: illegal option -- %s", argv[0], optarg);
          usage();
          return 1;
        }
        opt_filename = optarg;
    }
  }


	if (opt_count_bytes) {
		size_t bytes = 0;
		errno_t err = count_bytes(opt_filename, &bytes);
		
	}
}
