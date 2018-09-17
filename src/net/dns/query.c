#include <_net_.h>
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
static uint16_t opt_port = 53;
static char opt_name[256] = {0,};
static char opt_server[256] = {0,};

#define DNS_TYPE_A 1
#define DNS_TYPE_NS 2
#define DNS_TYPE_MD 3

#define DNS_CLASS_IN 1
#define DNS_CLASS_CS 2
#define DNS_CLASS_CH 3
#define DNS_CLASS_HS 4

typedef struct s_dns_header {
	uint16_t id;
	union {
		uint16_t u_flags;
		struct {
		uint16_t qr     : 1;
		uint16_t opcode : 4;
		uint16_t aa     : 1;
		uint16_t tc     : 1;
		uint16_t rd     : 1;
		uint16_t ra     : 1;
		uint16_t z      : 3;
		uint16_t rcode  : 4;
		} s_flags;
	} flags;
	uint16_t qdcount;
	uint16_t ancount;
	uint16_t nscount;
	uint16_t arcount;
} s_dns_header;

typedef struct s_dns_question {
	uint8_t qname[48];
	uint16_t qtype;
	uint16_t qclass;
} s_dns_question;

typedef struct s_dns_resource_record {
	char name[64];
	uint16_t type;
	uint16_t class;
	uint16_t ttl;
	uint16_t rdlength;
	uint16_t rdata;
} s_dns_resource_record;


typedef struct s_dns_request {
	s_dns_header header;
	s_dns_question question;
	s_dns_resource_record additional;
} s_dns_request;

void
qname(uint8_t *dst, uint8_t *name) {
	uint8_t src[48] = {0};
	size_t name_len = strlen((char*)name);
	strncpy((char*)src, (char*)name, name_len);
	src[name_len] = '.';

	for (uint8_t i=0, dot=0; i < name_len+1; i++) {
		if ('.' == src[i]) {
			*dst++ = i - dot;
			for (; dot < i; dot++) {
				*dst++ = src[dot];
			}
			dot++;
		}
	}
	*dst++ = 0;
}

void 
query(void) {
	sockfd_t sockfd;
	s_dns_request *msg = 0;
	int e;

#ifdef WINNT
	WSADATA wsa;
	e = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (e) {
		fprintf(stderr, "+WSAStartup failed\n");
		goto clean_exit;
	}
#endif

	sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (0 > sockfd) {
		fprintf(stderr, "! socket: %s\n", strerror(errno));
		goto clean_exit;
	}

	struct in_addr host;
	e = inet_pton(AF_INET, opt_server, &host);
	if (0 >= e) {
		fprintf(stderr, "! inet_pton: %s\n", strerror(errno));
		goto clean_exit;
	}

	struct sockaddr_in dest;
	socklen_t dest_len = sizeof(dest);
	memset(&dest, 0, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(opt_port);
	dest.sin_addr = host;

	msg = malloc(sizeof(s_dns_request));
	if (0 == msg) {
		fprintf(stderr, "! malloc: %s\n", strerror(errno));
		goto clean_exit;
	}
	memset(msg, 0, sizeof(s_dns_request));

	msg->header.id = htons(getpid());
	msg->header.flags.s_flags.rd = 1;
	msg->header.flags.u_flags = htons(msg->header.flags.u_flags);
	msg->header.qdcount = htons(1);
	qname(msg->question.qname, (uint8_t*)opt_name);
	msg->question.qtype = (uint16_t)DNS_TYPE_A;
	msg->question.qclass = (uint16_t)DNS_CLASS_IN;

	ssize_t n = sendto(sockfd,
										 msg,
										 sizeof(*msg),
										 0,
										 (const struct sockaddr*)&dest,
										 dest_len);
	if (0 > n) {
		fprintf(stderr, "! sendto: %s\n", strerror(errno));
		goto clean_exit;
	}

	/* n = recvfrom(sockfd, */
	/* 						 msg, */
	/* 						 sizeof(*msg), */
	/* 						 0, */
	/* 						 (struct sockaddr*)&dest, */
	/* 						 &dest_len); */
	/* if (0 > n) { */
	/* 	fprintf(stderr, "! recvfrom: %s\n", strerror(errno)); */
	/* 	goto clean_exit; */
	/* } */

 clean_exit:
	if (sockfd) {
		close(sockfd);
	}
	if (msg) {
		free(msg);
	}
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
	while (-1 != (ch = getopt_long(argc, argv, "hp:q:", longopts, 0))) {
		switch (ch) {
		case 'p':
			opt_port = (uint16_t)atoi(optarg);
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

	printf("; <<>> dnsq <<>> -q%s -p%d @%s\n",
				 opt_name,
				 opt_port,
				 opt_server);

	query();
	
 clean_exit:
	return 0;
}
