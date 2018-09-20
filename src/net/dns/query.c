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

#define DNS_QNAME_LEN 256

/* static char opt_service[INET_ADDRSTRLEN] = "http"; */
static uint16_t opt_port = 53;
static char opt_name[DNS_QNAME_LEN] = {0,};
static char opt_server[DNS_QNAME_LEN] = {0,};

#define DNS_TYPE_A 1
#define DNS_TYPE_NS 2
#define DNS_TYPE_MD 3

#define DNS_CLASS_IN 1
#define DNS_CLASS_CS 2
#define DNS_CLASS_CH 3
#define DNS_CLASS_HS 4

typedef struct s_dns_header {
	uint16_t id;
	struct h_flags {
#if (1 == NM_HAVE_LITTLE_ENDIAN)
		uint8_t rd     : 1;
		uint8_t tc     : 1;
		uint8_t aa     : 1;
		uint8_t opcode : 4;
		uint8_t qr     : 1;

		uint8_t rcode  : 4;
		uint8_t z      : 3;
		uint8_t ra     : 1;
#else
		uint8_t qr     : 1;
		uint8_t opcode : 4;
		uint8_t aa     : 1;
		uint8_t tc     : 1;
		uint8_t rd     : 1;

		uint8_t ra     : 1;
		uint8_t z      : 3;
		uint8_t rcode  : 4;
#endif
	} h_flags;
	uint16_t qdcount;
	uint16_t ancount;
	uint16_t nscount;
	uint16_t arcount;
} s_dns_header;

typedef struct s_dns_question {
	uint32_t qtype    : 16;
	uint32_t qclass   : 16;
} s_dns_question;

typedef struct s_dns_resource_record {
	char name[64];
	uint16_t type;
	uint16_t class;
	uint16_t ttl;
	uint16_t rdlength;
	uint16_t rdata;
} s_dns_resource_record;



void
make_qname(uint8_t *dst, uint8_t *name) {
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
	sockfd_t sockfd = 0;
	uint8_t *msg = 0;
	int e;

#ifdef WINNT
	WSADATA wsa;
	e = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (e) {
		fprintf(stderr, "+WSAStartup failed\n");
		goto clean_exit;
	}
#endif

	s_dns_header header;
	memset(&header, 0, sizeof(header));
	header.id = htons(getpid());
	header.h_flags.rd = 1;
	header.qdcount = htons(1);

	uint8_t qname[DNS_QNAME_LEN] = {0,};
	make_qname(qname, (uint8_t*)opt_name);

	s_dns_question question;
	memset(&question, 0, sizeof(question));
	question.qtype = htons(DNS_TYPE_A);
	question.qclass = htons(DNS_CLASS_IN);

	size_t msg_max_len = sizeof(s_dns_header)
		+ DNS_QNAME_LEN
		+ sizeof(s_dns_question);
	msg = malloc(msg_max_len);
	if (0 == msg) {
		fprintf(stderr, "! malloc: %s\n", strerror(errno));
		goto clean_exit;
	}
	memset(msg, 0, msg_max_len);

	size_t qname_len = strlen((char*)qname)+1;
	size_t msg_len = sizeof(header)
		+ qname_len
		+ sizeof(question);

	memcpy(msg, &header, sizeof(header));
	memcpy(msg+sizeof(header), qname, qname_len);
	memcpy(msg+sizeof(header)+qname_len, &question, sizeof(question));

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

	ssize_t n = sendto(sockfd,
										 msg,
										 msg_len,
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
