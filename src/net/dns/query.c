#include <netl.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static struct option longopts[] = {
	{"help",    no_argument,		  		0,      				'h'},
	{"port",    optional_argument,    0,              'p'},
	{"query",   required_argument,    0,              'q'},
	{0,         0,              			0,					     0}
};

static void 
usage(const char *p) {
	printf("Usage %s [options ...] host\n", p);
	printf("  -h, --help    this help text\n");
	printf("  -p, --port    send the query to a non-standard port, default port is 53\n");
	printf("  -q, --query   the domain name to query\n");
}


/* static char opt_service[INET_ADDRSTRLEN] = "http"; */
static int opt_port = 53;
static char opt_name[256] = {0,};
static char opt_server[256] = {0,};

void 
query(char* server, int port, char* name) {
	int sockfd;

	_unused_(server);
	_unused_(port);
	_unused_(name);
	
	sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
	if (sockfd < 0) {
		fprintf(stderr, "! socket: %s\n", strerror(errno));
		goto clean_exit;
	}

	struct hostent *host;
	host = gethostbyname(server);
	if (0 == host) {
		fprintf(stderr, "! gethostbyname: %s\n", strerror(errno));
		goto clean_exit;
	}
	
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	
	server_addr.sin_family = AF_INET;
	memcpy((char*)&server_addr.sin_addr.s_addr,
				 (const char*)host->h_addr,
				 host->h_length);
	server_addr.sin_port = htons(port);


clean_exit:
	close(sockfd);
}

int 
main(int argc, char* argv[]) {
	if (1 == argc) {
		usage(argv[0]);
		goto clean_exit;
	}

	int ch;
	while (-1 != (ch = getopt_long(argc, argv, "hp:q:", longopts, 0))) {
		switch (ch) {
		case 'p':
			opt_port = atoi(optarg);
			break;
		case 'q':
			strncpy(opt_name, optarg, strlen(optarg));
			break;
		default:
			usage(argv[0]);
			goto clean_exit;
		}
	}

	argc -= optind;
	argv += optind;

	if (0 < argc && '@' == argv[0][0]) {
		strncpy(opt_server, argv[0]+1, strlen(argv[0])-1);
	} else {
		strncpy(opt_server, "127.0.0.53", 12);
	}
	
	printf("--port=%d\n", opt_port);
	printf("--query=%s\n", opt_name);
	printf("@server=%s\n", opt_server);

	query(opt_server, opt_port, opt_name);
	
clean_exit:
	return 0;
}
