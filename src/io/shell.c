#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <getopt.h>
#include <sum.h>

static struct option longopts[] = {
	{"help",    no_argument,			    0,      				'h'},
	{"type",    required_argument,    0,				      't'},
	{"input",   required_argument,    0,      				'i'},
	{"output",  required_argument,    0,      				'o'},
	{0,         0,              0,       0}
};

static void usage(const char *p) {
	printf("usage %s\n", p);
	printf("  -h, --help\t\tthis help text\n");
	printf("  -t, --file\t\toperation type: file, etc.,\n");
	printf("  -i, --input\t\tinput file\n");
	printf("  -o, --output\t\toutputfile\n");
}

int op_file(const char *in, const char *out) {
	out;
	int v = out_seq(in);	
	return v; 
}

const char *opt_type; 		size_t OPT_TYPE_LEN = 16;
const char *opt_input;		size_t OPT_INPUT_LEN = 256;
const char *opt_output;		size_t OPT_OUTPUT_LEN = 256;

int main(int argc, char * *argv) {
	int ch;
	while (-1 != (ch = getopt_long(argc, argv, "ht:i:o:", longopts, 0))) {
		switch (ch) {
			case 't':
				opt_type = optarg;
				break;
			case 'i':
				opt_input = optarg;
				break;
			case 'o':
				opt_output = optarg;
				break;
			case 'h':
			default:
				usage(argv[0]);
				goto clean_exit;
		}
	}

	argc -= optind;
	argv += optind;

	if (0 == strncmp("file", opt_type, OPT_TYPE_LEN)) {
		op_file(opt_input, opt_output);
	} else {
		printf("panic type\n");
	}

clean_exit:
	return 0;
}
