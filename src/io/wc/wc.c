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
	
	FILE* file = fopen(name, "rb");
	if (!file) {
		return errno;
	}

	*count = count_delimeter(file, test);

	if (file) {
		fclose(file);
	}

	return 0;
}

int
test_byte(char c) {
	_unused_(c);
	return 1;
}

int
test_line(char c) {
	return ('\n' == c);
}

int
test_word(char c) {
	return (' ' == c);
}

enum op {
	OP_NONE,
	OP_BYTE,
	OP_WORD,
	OP_LINE,
};

typedef struct test_fn_s {
	const char *name;
	int (*test)(char);
} test_fn_s;

void
usage() {
  printf("Usage: /usr/bin/wc [OPTION]... [FILE]...\n");
	printf("Print newline, word, and byte counts for each FILE, and a total line if\n\
more than one FILE is specified.  A word is a non-zero-length sequence of\n\
characters delimited by white space.\n");
	printf("\nWith no FILE, or when FILE is -, read standard input.\n");
	printf("\nThe options below may be used to select which counts are printed, always in\n\
the following order: newline, word, character, byte, maximum line length.\n");
	printf("  -h, --help             print this message\n");
	printf("  -c, --bytes            print the byte counts\n");
	printf("  -l, --lines            print the newline counts\n");
	printf("  -w, --words            print the word counts\n");
}


static struct option long_options[] = {
			{"help",  no_argument, 0, 'h'},
			{"bytes", no_argument, 0, 'c'},
			{"lines", no_argument, 0, 'l'},
			{"words", no_argument, 0, 'w'},
			{0,       0,           0,  0 },
};

int 
main(int argc, char **argv) {
	static test_fn_s test_fn_table[] = {
		{0, 0},
		{"byte", test_byte},
		{"word", test_word},		
		{"line", test_line},
	};

	#define filename_size 16
  char *opt_filename[filename_size] = {0};
	test_fn_s *opt_count_test[sizeof(test_fn_table)/sizeof(test_fn_s)] = {0};
	int opt_count_idx = 0;
	
  int ch;
  while (-1 != (ch = getopt_long(argc, argv, "hcwl", long_options, 0))) {
    switch (ch) {
		case 'h':
			usage();
			return 0;
		case 'c':
			opt_count_test[opt_count_idx++] = &test_fn_table[OP_BYTE];
			break;
		case 'w':
			opt_count_test[opt_count_idx++] = &test_fn_table[OP_WORD];
			break;
		case 'l':
			opt_count_test[opt_count_idx++] = &test_fn_table[OP_LINE];
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
    for (test_fn_s **p=opt_count_test; *p; p++) {
			size_t count = count_delimeter(stdin, (*p)->test);
			printf("# [%s]=%zu\n", (*p)->name, count);
    }
		return 0;
	}

	/* for (char **filename=opt_filename; *filename; filename++) { */
	/* 	char out_buf[2048] = {0}; */
	/* 	int out_idx = 0; */
	/* 	int has_error = 0; */

	/* 	out_idx += sprintf(out_buf, "%s", *filename); */
		
	/* 	for (test_fn_s **p=opt_count_test; *p; p++) { */
	/* 		size_t count = 0; */
	/* 		int e = count_file(*filename, */
	/* 											 &count, */
	/* 											 count_delimeter, */
	/* 											 (*p)->test); */
	/* 		if (e) { */
	/* 			has_error += e; */
	/* 			out_idx += sprintf(out_buf+out_idx, */
	/* 												 " [%s]?%s", */
	/* 												 (*p)->name, */
	/* 												 strerror(e)); */
	/* 		} else { */
	/* 			out_idx += sprintf(out_buf+out_idx, */
	/* 												 " [%s]=%zu", */
	/* 												 (*p)->name, */
	/* 												 count); */
	/* 		} */
	/* 	} */
	/* 	printf("%s %s\n", (has_error ? "!" : "#"), out_buf); */
	/* } */
}
