#include <netl.h>

static struct option longopts[] = {
	{"help",    no_argument,		  		0,      				'h'},
	{"4",    		no_argument,    			0,			    		'4'},
	{"6",    		no_argument,   				0,			    		'6'},
	{0,         0,              			0,					     0}
};

static void 
usage(const char *p) {
	printf("usage %s [options ...] host\n", p);
	printf("  -h, --help\t\tthis help text\n");
	printf("  -4, --4\t\tIPv4, it is default\n");
	printf("  -6, --6\t\tIPv6\n");
}


static int opt_type = AF_INET;

void 
get_ipv4_addr(const char* host) {
	struct addrinfo hints;
	struct addrinfo* res;

	memset(&hints, 0, sizeof(struct addrinfo));
	int s = getaddrinfo(host, 0, &hints, &res);
	if (s) {
		//fprintf(stderr, "get_ipv4_addr: %s\n", gai_strerror(s));
	}
	_unused_(hints);
	freeaddrinfo(res);	
}

void 
get_ipv6_addr(const char* host) {

}


int 
main(int argc, char* argv[]) {
	if (1 == argc) {
		usage(argv[0]);
		goto clean_exit;
	}

	int ch;
	while (-1 != (ch = getopt_long(argc, argv, "h46", longopts, 0))) {
		switch (ch) {
			case '4':
				opt_type = AF_INET;
				break;
			case '6':
				opt_type = AF_INET6;
				break;
			case 'h':
			default:
				usage(argv[0]);
				goto clean_exit;
		}
	}

	argc -= optind;
	argv += optind;

	for (int i=0; i < argc; ++i) {
		if (AF_INET6 == opt_type) {
			get_ipv6_addr(argv[i]);
		} else {
			get_ipv4_addr(argv[i]);
		}
	}

clean_exit:
	return 0;
}
