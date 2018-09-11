#include <netl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <getopt.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>

static struct option longopts[] = {
	{"help",    no_argument,		  		0,      				'h'},
	{"4",    		no_argument,    			0,			    		'4'},
	{"6",    		no_argument,   				0,			    		'6'},
	{"service",	optional_argument,  	0,			    		's'},
	{0,         0,              			0,					     0}
};

static void 
usage(const char *p) {
	printf("usage %s [options ...] host\n", p);
	printf("  -h, --help\t\tthis help text\n");
	printf("  -4, --4\t\tIPv4\n");
	printf("  -6, --6\t\tIPv6\n");
	printf("  -s, --service\t\tservice name: port or name\n");
}


static int opt_family = AF_UNSPEC;
static char opt_service[INET_ADDRSTRLEN] = {0, };


void 
get_ip_addr(const char* host, const char* service, const int family) {
	struct addrinfo hints, *res;
	int e;

	printf("Hostname: %s\n", host);

	if (AF_INET == family || AF_INET6 == family) {
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = family;
		hints.ai_socktype = SOCK_STREAM;
		e = getaddrinfo(host, service, &hints, &res);
	} else {
		_unused_(hints);
		e = getaddrinfo(host, service, 0, &res);		
	}

	if (e) {
		fprintf(stderr, "  +get_ip_addr: %s\n", gai_strerror(e));
		goto clean_exit;
	}
	
	for (struct addrinfo* p=res; p != 0; p=p->ai_next) {
		if (AF_INET == p->ai_family) {
			struct sockaddr_in* in = (struct sockaddr_in *)p->ai_addr;
			void* a = &(in->sin_addr);
			char s[INET_ADDRSTRLEN]; 
			inet_ntop(p->ai_family, a, s, sizeof(s));
			printf("  +IPv4 Address: %s\n", s);
		} else if (AF_INET6 == p->ai_family) {
			struct sockaddr_in6* in = (struct sockaddr_in6 *)p->ai_addr;
			void* a = &(in->sin6_addr);
			char s[INET6_ADDRSTRLEN]; 
			inet_ntop(p->ai_family, a, s, sizeof(s));
			printf("  +IPv6 Address: %s\n", s);
		}
	}


clean_exit:
	freeaddrinfo(res);	
}

int 
main(int argc, char* argv[]) {
	if (1 == argc) {
		usage(argv[0]);
		goto clean_exit;
	}

	int ch;
	while (-1 != (ch = getopt_long(argc, argv, "h46s:", longopts, 0))) {
		switch (ch) {
			case '4':
				opt_family = AF_INET;
				break;
			case '6':
				opt_family = AF_INET6;
				break;
			case 's':
				strncpy(opt_service, optarg, sizeof(opt_service));
				break;
			case 'h':
			default:
				usage(argv[0]);
				goto clean_exit;
		}
	}

	argc -= optind;
	argv += optind;

	if (AF_UNSPEC == opt_family) {
		opt_family = AF_INET;
	}

	if (0 == opt_service[0]) {
		strncpy(opt_service, "http", 4);
	}

	for (int i=0; i < argc; ++i) {
		get_ip_addr(argv[i], opt_service, opt_family);
	}

clean_exit:
	return 0;
}
