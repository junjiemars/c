#include <_io_.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>


size_t
count_delimeter(FILE *in, int (*test)(char)) {
	size_t count = 0;
	char byte;
	while (1 == fread(&byte, sizeof(char), 1, in)) {
		if (test(byte)) {
			count++;
		}
	}
	return count;
}

int
count_file(const char * name,
					 size_t *count,
					 size_t (*count_delimeter)(FILE*, int (*)(char)),
					 int (*test)(char)) {
	
	FILE* file = fopen(name, "r");
	if (!file) {
		return errno;
	}

	*count = count_delimeter(file, test);

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


#define OP_MAP(XX)              \
	XX(0, NONE, "none")						\
	XX(1, BYTE, "count bytes")    \
	XX(2, LINE, "count lines")    \

enum op {
#define XX(num, name, string) OP_##name = num,
	OP_MAP(XX)
#undef XX
};

#define filename_size 16

#define fn_test(x)                                  \
	(OP_LINE == ((x) & OP_LINE) ? test_line           \
	 : (OP_BYTE == ((x) & OP_BYTE)) ? test_byte : 0)

#define str_test(x)                                 \
	(OP_LINE == ((x) & OP_LINE) ? "line"              \
	 : (OP_BYTE == ((x) & OP_BYTE)) ? "byte" : 0)


int 
main(int argc, char **argv) {
	int opt_count_test = OP_NONE;

  char *opt_filename[filename_size] = {0};

  int ch;
  while (-1 != (ch = getopt(argc, argv, "hcl"))) {
    switch (ch) {
		case 'h':
			usage();
			return 0;
		case 'c':
			opt_count_test = OP_BYTE;
			break;
		case 'l':
			opt_count_test = OP_LINE;
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

	if (!*opt_filename) {
		size_t count = count_delimeter(stdin, fn_test(opt_count_test));
		printf("# [%s]=%zu\n", str_test(opt_count_test), count);
		return 0;
	}

	size_t total = 0;
	
	for (char **filename=opt_filename; *filename; filename++) {
		size_t count = 0;
		int e = count_file(*filename, &count, count_delimeter, fn_test(opt_count_test));
		if (e) {
			printf("! %s [%s]=%s\n", *filename, str_test(opt_count_test), strerror(e));
		} else {
			total += count;
			printf("# %s [%s]=%zu\n", *filename, str_test(opt_count_test), count);
		}
	}
		
	printf("# total [%s]=%zu\n", str_test(opt_count_test), total);
}
