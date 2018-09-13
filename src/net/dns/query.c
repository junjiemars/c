#include <netl.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>

static struct option longopts[] = {
	{"help",    no_argument,		  		0,      				'h'},
	{0,         0,              			0,					     0}
};

static void 
usage(const char *p) {
	printf("Usage %s [options ...] host\n", p);
	printf("  -h, --help\t\tthis help text\n");
}


/* static char opt_service[INET_ADDRSTRLEN] = "http"; */


void 
get_ip_addr(const char* host) {
	struct addrinfo hints, *res;
	int e; /* error no */
	
#ifdef WINNT
	WSADATA wsa;
	e = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (e) {
		fprintf(stderr, "+WSAStartup failed\n");
	}
#endif
	
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; /* IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	printf("Hostname: %s\n", host);

	e = getaddrinfo(host, 0, &hints, &res);		
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
#ifdef WINNT
	WSACleanup();
#endif
}

int 
main(int argc, char* argv[]) {
	if (1 == argc) {
		usage(argv[0]);
		goto clean_exit;
	}

	int ch;
	while (-1 != (ch = getopt_long(argc, argv, "h", longopts, 0))) {
		switch (ch) {
			default:
				usage(argv[0]);
				goto clean_exit;
		}
	}

	argc -= optind;
	argv += optind;

	for (int i=0; i < argc; ++i) {
		get_ip_addr(argv[i]);
	}

clean_exit:
	return 0;
}
