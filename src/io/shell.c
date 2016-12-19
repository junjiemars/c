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

int op_file(char *in, const char *out) {
	int v = out_seq(in);	
	return v; 
}

char opt_type[16] = {0};
char opt_input[256] = {0};
char opt_output[256] = {0};

int main(int argc, char * *argv) {
	int ch;
	while (-1 != (ch = getopt_long(argc, argv, "ht:i:o:", longopts, 0))) {
		switch (ch) {
			case 't':
				strncpy(opt_type, optarg, sizeof(opt_type));
				break;
			case 'i':
				strncpy(opt_input, optarg, sizeof(opt_input));
				break;
			case 'o':
				strncpy(opt_output, optarg, sizeof(opt_output));
				break;
			case 'h':
			default:
				usage(argv[0]);
				goto clean_exit;
		}
	}

	argc -= optind;
	argv += optind;

	if (0 == strncmp("file", opt_type, sizeof(opt_type))) {
		op_file(opt_input, opt_output);
	} else {
		printf("panic type\n");
	}

clean_exit:
	return 0;
}
