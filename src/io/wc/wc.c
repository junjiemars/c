#include <_io_.h>
#include <stdio.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct count_test_s {
	int (*test_line)(char);
	int (*test_word)(char, char);
	int (*test_char)(char, char);
	int (*test_byte)(char);
	void (*test_max_line_length)(char, size_t*, size_t*);
} count_test_s;

typedef struct count_unit_s {
	char *filename;
	int error;
	size_t lines;
	size_t words;
	size_t chars;
	size_t bytes;
	size_t max_line_length;
	size_t cur_line_length;
} count_unit_s;

typedef struct count_state_s {
	int idx;
	count_test_s test;
	count_unit_s *unit;
	size_t total_lines;
	size_t total_words;
	size_t total_chars;
	size_t total_bytes;
	size_t max_total;
	size_t max_max_line_length;
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

	char current = 0, previous = 0;
	while (1 == fread(&current, sizeof(char), 1, file)) {
		if (test->test_line && test->test_line(current)) {
			unit->lines++;
			state->total_lines++;
			if (state->max_total < state->total_lines) {
				state->max_total = state->total_lines;
			}
		}

		if (test->test_word && test->test_word(current, previous)) {
			unit->words++;
			state->total_words++;
			if (state->max_total < state->total_words) {
				state->max_total = state->total_words;
			}
		}

		if (test->test_char) {
			int n = test->test_char(current, previous);
			unit->chars += n;
			state->total_chars += n;
			if (state->max_total < state->total_chars) {
				state->max_total = state->total_chars;
			}
		}

		if (test->test_byte && test->test_byte(current)) {
			unit->bytes++;
			state->total_bytes++;
			if (state->max_total < state->total_bytes) {
				state->max_total = state->total_bytes;
			}
		}

		if (test->test_max_line_length) {
			test->test_max_line_length(current,
																 &unit->max_line_length,
																 &unit->cur_line_length);
			if (state->max_max_line_length < unit->max_line_length) {
				state->max_max_line_length = unit->max_line_length;
			}
		}

		previous = current;
	}

	if (!is_stdin && file) {
		fclose(file);
	}

	if (test->test_word && test->test_word(0, previous)) {
		unit->words++;
		state->total_words++;
		if (state->max_total < state->total_words) {
			state->max_total = state->total_words;
		}
	}
}

int
test_line(char c) {
	return ('\n' == c);
}

int
test_word(char c, char p) {
	return (0 != p && !isspace(p) && (isspace(c) || 0 == c));
}

int
test_char(char c, char p) {
	if ((0xc0 & c) == 0xc0) {
		return 1;
	} else if ((0x80 & c) == 0x80
						 && (((0xc0 & p) == 0xc0)
								 || (0x80 & p) == 0x80)) {
		return 0;
	} else {
		return 1;
	}
}

int
test_byte(char c) {
	return (0 != c);
}

void
test_max_line_length(char c, size_t *max, size_t *cur) {
	if (test_line(c)) {
		if (*max < *cur) {
			*max = *cur;
		}
		*cur = 0;
	} else {
		(*cur)++;
	}
}

void print_state(count_state_s *state) {
	int max_len = 1;
	count_test_s *test = &state->test;

	/* just stdin and one option: easy to parse the result*/
	if (1 == state->idx && '-' == state->unit[0].filename[0]
			&& (1 == (test->test_line ? 1 : 0)
					+ (test->test_word ? 1 : 0)
					+ (test->test_char ? 1 : 0)
					+ (test->test_byte ? 1 : 0)
					+ (test->test_max_line_length ? 1 : 0))) {
		size_t n = (test->test_max_line_length
								? state->max_max_line_length : state->max_total);
		printf("%zu\n", n);
		return;
	}

	if (state->max_total < 10) {
		max_len += 1;
	} else {
		size_t val = state->max_total;
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
		if (test->test_char) {
			printf("%*zu ", max_len, unit->chars);
		}
		if (test->test_byte) {
			printf("%*zu ", max_len, unit->bytes);
		}
		if (test->test_max_line_length) {
			printf("%*zu ", max_len, unit->max_line_length);
		}
		if (unit->error) {
			printf(" %s@%s\n", unit->filename, strerror(unit->error));			
		} else {
			printf(" %s\n", unit->filename);
		}
	}

	if (1 < state->idx) {
		if (test->test_line) {
			printf("%*zu ", max_len, state->total_lines);
		}
		if (test->test_word) {
			printf("%*zu ", max_len, state->total_words);
		}
		if (test->test_char) {
			printf("%*zu ", max_len, state->total_chars);
		}
		if (test->test_byte) {
			printf("%*zu ", max_len, state->total_bytes);
		}
		if (test->test_max_line_length) {
			printf("%*zu ", max_len, state->max_max_line_length);
		}
		printf(" %s\n", "total");
	}
}

void
usage(const char *wc) {
  printf("Usage: %s [OPTION]... [FILE]...\n", wc);
	printf("\n");
	printf("Print newline, word, and byte counts for each FILE, and a total line if\n\
more than one FILE is specified.  A word is a non-zero-length sequence of\n\
characters delimited by white space.\n");
	printf("\nWith no FILE, or when FILE is -, read standard input.\n");
	printf("\nThe options below may be used to select which counts are printed, always in\n\
the following order: newline, word, char, byte, maximum line length.\n");
	printf("  -h, --help             print this message\n");
	printf("  -l, --lines            print the newline counts\n");
	printf("  -w, --words            print the word counts\n");
	printf("  -m, --chars            print the char(utf-8) counts\n");
	printf("  -c, --bytes            print the byte counts\n");
	printf("  -L, --max-line-length  print the maximum width in bytes\n");
}

static struct option long_options[] = {
			{"help",   no_argument,   0, 'h'},
			{"bytes",  no_argument,   0, 'c'},
			{"lines",  no_argument,   0, 'l'},
			{"chars",  no_argument,   0, 'm'},
			{"words",  no_argument,   0, 'w'},
			{"max-line-length", no_argument, 0, 'L'},
			{0,        no_argument,   0, '-'},
			{0,        0,             0,  0 },
};

static int opt_has_lines = 0;
static int opt_has_words = 0;
static int opt_has_chars = 0;
static int opt_has_bytes = 0;
static int opt_has_max_line_length = 0;
static int opt_has_from_stdin = 0;
static int opt_has_none = 0;

static count_state_s state;

void
on_exiting(void) {
	if (state.unit) {
		free(state.unit);
	}
}

int 
main(int argc, char **argv) {
  int ch;
  while (-1 != (ch = getopt_long(argc, argv, "hlwmcL-", long_options, 0))) {
    switch (ch) {
		case 'h':
			usage(argv[0]);
			return 0;
		case 'l':
			opt_has_lines = 1;
			break;
		case 'w':
			opt_has_words = 1;
			break;
		case 'm':
			opt_has_chars = 1;
			break;
		case 'c':
			opt_has_bytes = 1;
			break;
		case 'L':
			opt_has_max_line_length = 1;
			break;
		case '-':
			opt_has_from_stdin++;
			opt_has_none = 1;
			break;
		default:
			if ('-' == optarg[0]) {
				printf("%s: illegal option -- %s", argv[0], optarg);
			}
			usage(argv[0]);
			return -1;
    }
  }

	memset(&state, 0, sizeof(state));

	int files_count = argc - optind;
	if (0 == files_count) {
		opt_has_from_stdin++;
		files_count++;
	}
	
	state.unit = malloc(sizeof(count_unit_s) * files_count);
	memset(state.unit, 0, sizeof(count_unit_s) * files_count);
	atexit(&on_exiting);
	
	if (opt_has_none) {
		state.test.test_line = test_line;
		state.test.test_word = test_word;
		state.test.test_byte = test_byte;
	} else {
		state.test.test_line = (opt_has_lines ? test_line : 0);
		state.test.test_word = (opt_has_words ? test_word : 0);
		state.test.test_char = (opt_has_chars ? test_char : 0);
		state.test.test_byte = (opt_has_bytes ? test_byte : 0);
		state.test.test_max_line_length = (opt_has_max_line_length
																			 ? test_max_line_length : 0);
	}

	if (opt_has_from_stdin) {
		state.unit[state.idx].filename = "-";
		count(&state);
		state.idx++;
	}

	for (int i=optind; i < argc; i++) {
    state.unit[state.idx].filename = argv[i];
		count(&state);
		state.idx++;
	}	

	print_state(&state);
}
