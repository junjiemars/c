#include <netl.h>

static struct option longopts[] = {
	{"help",    no_argument,		  		0,      				'h'},
	{"type",    optional_argument,    0,					    't'},
	{"node",    required_argument,    0,      				'n'},
	{0,         0,              			0,					     0}
};

static void 
usage(const char *p) {
	printf("usage %s\n", p);
	printf("  -h, --help\t\tthis help text\n");
	printf("  -t, --type\t\tIPv4 or IPv6, default is IPv4\n");
	printf("  -n, --node\t\tthe node want to resolve\n");
}


//static char node4[INET_ADDRSTRLEN];
//static struct addrinfo ai;
// 
//void get_ipv4_addr() {
//	
//}


int main(int argc, char* argv[]) {
	if (1 == argc) {
		usage(argv[0]);
		goto clean_exit;
	}

	int ch;
	while (-1 != (ch = getopt_long(argc, argv, "ht:n:", longopts, 0))) {
		switch (ch) {
			case 't':
				//opt_type = optarg;
				break;
			case 'n':
				//opt_input = optarg;
				break;
			case 'h':
			default:
				usage(argv[0]);
				goto clean_exit;
		}
	}

	argc -= optind;
	argv += optind;

clean_exit:
	return 0;
}
