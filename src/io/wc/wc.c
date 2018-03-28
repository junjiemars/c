#include <_io_.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>



int
count_file(const char * name, size_t *count, int (*test)(char)) {
	FILE* file = fopen(name, "rb");
	if (!file) {
		return errno;
	}

	char byte;
	while (1 == fread(&byte, sizeof(char), 1, file)) {
		if (test(byte)) {
			(*count)++;
		}
	}

	if (file) {
		fclose(file);
	}

	return 0;
}

void
usage() {
  printf("usage: wc [-cl] [file ...]\n");
}

int
test_byte(char byte) {
	_unused_(byte);
	return 1;
}

int
test_line(char line) {
	return ('\n' == line);
}

#define filename_size 16
#define fn_test(x) (2 == ((x) & 2) ? test_line : test_byte)
#define str_test(x) (2 == ((x) & 2) ? "line" : "byte")

int 
main(int argc, char **argv) {
	int opt_count_test = 0;

  char *opt_filename[filename_size] = {0};

  int ch;
  while (-1 != (ch = getopt(argc, argv, "cl"))) {
    switch (ch) {
      case 'c':
        opt_count_test = 1;
        break;
      case 'l':
        opt_count_test = 2;
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
	
	for (char **filename=opt_filename; *filename; filename++) {
		size_t count = 0;
		int e = count_file(*filename, &count, fn_test(opt_count_test));
		if (e) {
			printf("! %s [%s]=%s\n", *filename, str_test(opt_count_test), strerror(e));
		} else {
			total += count;
			printf("# %s [%s]=%zu\n", *filename, str_test(opt_count_test), count);
		}
	}
		
	printf("# total [%s]=%zu\n", str_test(opt_count_test), total);
}
