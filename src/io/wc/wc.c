#include <_io_.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>

void
usage() {
  printf("usage: wc [-cl] [file ...]\n");
}

int
count_bytes(const char * name, size_t *count) {
	FILE* file = fopen(name, "rb");
	if (!file) {
		return errno;
	}

	char byte;
	while (1 == fread(&byte, sizeof(char), 1, file)) {
		(*count)++;
	}

	if (file) {
		fclose(file);
	}

	return 0;
}

int 
main(int argc, char **argv) {
  int opt_count_bytes = 1;
  int opt_count_lines = 1;
	#define filename_size 16
  char *opt_filename[filename_size] = {0};

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
        }
				usage();
				return -1;
    }
  }

	for (int i=optind, j=0; i < argc && j < filename_size; i++, j++) {
		opt_filename[j] = argv[i];
	}

	size_t total = 0;
	
	if (opt_count_bytes) {
		for (char **filename=opt_filename; *filename; filename++) {
			size_t bytes = 0;
			int e = count_bytes(*filename, &bytes);
			if (e) {
				printf("! %s [byte]=%s\n", *filename, strerror(e));
			} else {
				total += bytes;
				printf("# %s [byte]=%zu\n", *filename, bytes);
			}			
		}

		printf("# total [byte]=%zu\n", total);
	}


}
