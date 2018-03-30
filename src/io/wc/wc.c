#include <_io_.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>

#define filename_size 16

typedef struct count_test_s {
	int (*test_line)(char);
	int (*test_byte)(char);
	int (*test_word)(char);			
} count_test_s;

typedef struct count_unit_s {
	char *filename;
	int error;
	size_t lines;
	size_t words;
	size_t bytes;
} count_unit_s;

typedef struct count_state_s {
	int idx;
	count_test_s test;
	count_unit_s unit[filename_size];
	size_t total_lines;
	size_t total_words;
	size_t total_bytes;
} count_state_s;


void
count(count_state_s *state) {
	FILE *file = stdin;
	int is_stdin = 0;
	count_unit_s *unit = &state->unit[state->idx];
	count_test_s *test = &state->test;
	
	if (0 == unit->filename || '-' == unit->filename[0]) {
		is_stdin = 1;
	} else {
		file = fopen(unit->filename, "rb");
		if (!file) {
			unit->error = errno;
			return;
		}
	}

	char byte;
	while (1 == fread(&byte, sizeof(char), 1, file)) {
		if (test->test_line && test->test_line(byte)) {
			unit->lines++;
		}

		if (test->test_byte && test->test_byte(byte)) {
			unit->bytes++;
		}

		if (test->test_word) {
			if (test->test_word(byte)) {
				unit->words++;
			} 
		}
	}

	if (!is_stdin && file) {
		fclose(file);
	}
}

int
test_line(char c) {
	return ('\n' == c);
}

int
test_word(char c) {
	return (' ' == c);
}

int
test_byte(char c) {
	_unused_(c);
	return 1;
}

void print_state(count_state_s *state) {
	size_t max = 0;
	size_t max_total = 0;
	count_test_s *test = &state->test;
	
	for (int i=0; i<state->idx; i++) {
		count_unit_s *unit = &state->unit[i];
		
		if (test->test_line) {
			state->total_lines += unit->lines;
			if (max < unit->lines) {
				max = unit->lines;
			}
			if (max_total < state->total_lines) {
				max_total = state->total_lines;
			}
		}
		
		if (test->test_word) {
			state->total_words += unit->words;
			if (max < unit->words) {
				max = unit->words;
			}
			if (max_total < state->total_words) {
				max_total = state->total_words;
			}
		}
		
		if (test->test_byte) {
			state->total_bytes += unit->bytes;
			if (max < unit->bytes) {
				max = unit->bytes;
			}
			if (max_total < state->total_bytes) {
				max_total = state->total_bytes;
			}
		}
	}

	if (1 < state->idx && max < max_total) {
		max = max_total;
	}

	int max_len = 1;
	if (max < 10) {
		max_len += 1;
	} else {
		size_t val = max;
		while (val > 9) {
			val /= 10;
			max_len++;
		}
	}
	
	for (int i=0; i<state->idx; i++) {
		count_unit_s *unit = &state->unit[i];
		
		if (test->test_line) {
			printf("%*zu ", max_len, unit->lines);
		}
		if (test->test_word) {
			printf("%*zu ", max_len, unit->words);
		}
		if (test->test_byte) {
			printf("%*zu ", max_len, unit->bytes);
		}
		printf(" %s\n", unit->filename);
	}

	if (1 < state->idx) {
		if (test->test_line) {
			printf("%*zu ", max_len, state->total_lines);
		}
		if (test->test_word) {
			printf("%*zu ", max_len, state->total_words);
		}
		if (test->test_byte) {
			printf("%*zu ", max_len, state->total_bytes);
		}
		printf(" %s\n", "total");
	}
}

void
usage() {
  printf("Usage: /usr/bin/wc [OPTION]... [FILE]...\n");
	printf("  or:  /usr/bin/wc [OPTION]... --files0-from=F\n");
	printf("Print newline, word, and byte counts for each FILE, and a total line if\n\
more than one FILE is specified.  A word is a non-zero-length sequence of\n\
characters delimited by white space.\n");
	printf("\nWith no FILE, or when FILE is -, read standard input.\n");
	printf("\nThe options below may be used to select which counts are printed, always in\n\
the following order: newline, word, character, byte, maximum line length.\n");
	printf("  -h, --help             print this message\n");
	printf("  -l, --lines            print the newline counts\n");
	printf("  -w, --words            print the word counts\n");
	printf("  -c, --bytes            print the byte counts\n");
}

static int opt_has_lines = 0;
static int opt_has_words = 0;
static int opt_has_bytes = 0;
static int opt_has_from_stdin = 0;
static int opt_has_none = 1;

static struct option long_options[] = {
			{"help",   no_argument,   0, 'h'},
			{"bytes",  no_argument,   0, 'c'},
			{"lines",  no_argument,   0, 'l'},
			{"words",  no_argument,   0, 'w'},
			{0,        no_argument,   0, '-'},
			{0,        0,             0,  0 },
};

int 
main(int argc, char **argv) {
	count_state_s state = {0};
  char *opt_filename[filename_size] = {0};
	
  int ch;
  while (-1 != (ch = getopt_long(argc, argv, "hcwl-", long_options, 0))) {
    switch (ch) {
		case 'h':
			usage();
			return 0;
		case 'c':
			opt_has_bytes = 1;
			opt_has_none = 0;
			break;
		case 'w':
			opt_has_words = 1;
			opt_has_none = 0;
			break;
		case 'l':
			opt_has_lines = 1;
			opt_has_none = 0;
			break;
		case '-':
			opt_has_from_stdin = 1;
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

	if (opt_has_none) {
		state.test.test_line = test_line;
		state.test.test_word = test_word;
		state.test.test_byte = test_byte;
	} else {
		state.test.test_line = (opt_has_lines ? test_line : 0);
		state.test.test_word = (opt_has_words ? test_word : 0);
		state.test.test_byte = (opt_has_bytes ? test_byte : 0);
	}

	if (!*opt_filename || opt_has_from_stdin) {
		state.unit[state.idx].filename = "-";
		count(&state);
		state.idx++;
	}

	for (char **filename=opt_filename; *filename; filename++) {
    state.unit[state.idx].filename = *filename;
		count(&state);
		state.idx++;
	}	

	print_state(&state);
}
