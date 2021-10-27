#include "_net_.h"
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/*
 * References:
 * 1. https://datatracker.ietf.org/doc/html/rfc1034
 * 2. https://datatracker.ietf.org/doc/html/rfc1035
 *
*/


#define DNS_TYPE_A     0x0001
#define DNS_TYPE_NS    0x0002
#define DNS_TYPE_MD    0x0003

#define DNS_CLASS_IN   0x0001
#define DNS_CLASS_CS   0x0002
#define DNS_CLASS_CH   0x0003
#define DNS_CLASS_HS   0x0004

#define DNS_QNAME_MAX_LEN    255
#define DNS_LABEL_MAX_LEN    63
#define DNS_UDP_MSG_MAX_LEN  512


/* header section */
typedef struct s_dns_hs
{
  uint16_t id;
  struct h_flags
  {
    uint8_t qr     : 1;
    uint8_t opcode : 4;
    uint8_t aa     : 1;
    uint8_t tc     : 1;
    uint8_t rd     : 1;
    uint8_t ra     : 1;
    uint8_t z      : 3;
    uint8_t rcode  : 4;
  } h_flags;
  uint16_t qdcount;
  uint16_t ancount;
  uint16_t nscount;
  uint16_t arcount;
} s_dns_hs;


/* question section */
typedef struct s_dns_qs
{
  uint32_t qtype    : 16;
  uint32_t qclass   : 16;
} s_dns_qs;


/* resource record */
typedef struct s_dns_rr
{
  char name[64];
  uint16_t type;
  uint16_t class;
  uint16_t ttl;
  uint16_t rdlength;
  uint16_t rdata;
} s_dns_rr;


static void make_label(uint8_t *dst, uint8_t *name);
static void query(void);


static struct option longopts[]  =
  {
    { "help",    no_argument,          0,              'h' },
    { "server",  optional_argument,    0,              's' },
    { "port",    optional_argument,    0,              'p' },
    { "query",   required_argument,    0,              'q' },
    { 0,         0,                    0,               0  }
  };

static void
usage(const char *p)
{
  printf("Usage %s [options ...] host\n", p);
  printf("  -h, --help    this help text\n");
  printf("  -s  --server  DNS server, default is 127.0.0.53\n");
  printf("  -p, --port    query a non-standard port, default is 53\n");
  printf("  -q, --query   the domain name to query\n");
}


/* static char opt_service[INET_ADDRSTRLEN] = "http"; */
static uint16_t  opt_port              =  53;
static char opt_name[DNS_QNAME_MAX_LEN]    =  { 0, };
static char opt_server[DNS_QNAME_MAX_LEN]  =  "127.0.0.53";


void
make_label(uint8_t *dst, uint8_t *name)
{
  uint8_t  *p, **pre, len;

  p = name;
  pre = &name;

  while (1)
    {
      if ('.' == *p || 0 == *p)
        {
          len = p - *pre;
          *dst++ = len;
          memcpy(dst, *pre, len);
          dst += len;
          *pre = p + 1;
          
          if (0 == *p)
            {
              *dst = 0;
              break;
            }
        }
      p++;
    }
}

void
query(void)
{
  int                  rc;
  s_dns_hs         header;
  uint8_t              qname[DNS_QNAME_MAX_LEN];
  size_t               qname_len;
  s_dns_qs       question;
  sockfd_t             sfd;
  uint8_t             *msg;
  size_t               msg_len;
  size_t               msg_max_len;
  struct in_addr       host;
  struct sockaddr_in   dst;
  socklen_t            dst_len;
  ssize_t              n ;

#ifdef WINNT
  WSADATA wsa;
  rc= WSAStartup(MAKEWORD(2, 2), &wsa);
  if (rc)
    {
      fprintf(stderr, "!WSAStartup failed\n");
      goto clean_exit;
    }
#endif

  /* make header */
  memset(&header, 0, sizeof(header));
  header.id = htons(getpid());
  header.h_flags.rd = 1;
  header.qdcount = htons(1);

  make_label(qname, (uint8_t*) opt_name);

  /* make question */
  memset(&question, 0, sizeof(question));
  question.qtype = htons(DNS_TYPE_A);
  question.qclass = htons(DNS_CLASS_IN);

  msg_max_len = sizeof(s_dns_hs) + DNS_QNAME_MAX_LEN + sizeof(s_dns_qs);
  msg = malloc(msg_max_len);
  if (0 == msg)
    {
      fprintf(stderr, "!malloc: %s\n", strerror(errno));
      goto clean_exit;
    }
  memset(msg, 0, msg_max_len);

  qname_len = strlen((char*) qname) + 1;
  msg_len = sizeof(header) + qname_len + sizeof(question);

  memcpy(msg, &header, sizeof(header));
  memcpy(msg+sizeof(header), qname, qname_len);
  memcpy(msg+sizeof(header)+qname_len, &question, sizeof(question));

  sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (0 > sfd)
    {
      fprintf(stderr, "! socket: %s\n", strerror(errno));
      goto clean_exit;
    }

  rc= inet_pton(AF_INET, opt_server, &host);
  if (rc <= 0)
    {
      fprintf(stderr, "!inet_pton: %s\n", strerror(errno));
      goto clean_exit;
    }

  dst_len = sizeof(dst);
  memset(&dst, 0, sizeof(dst));
  dst.sin_family = AF_INET;
  dst.sin_port = htons(opt_port);
  dst.sin_addr = host;

  n = sendto(sfd,
             msg,
             msg_len,
             0,
             (const struct sockaddr*)&dst,
             dst_len);
  if (0 > n)
    {
      fprintf(stderr, "!sendto: %s\n", strerror(errno));
      goto clean_exit;
    }

  /* n = recvfrom(sfd, */
  /*               msg, */
  /*               sizeof(*msg), */
  /*               0, */
  /*               (struct sockaddr*)&dst, */
  /*               &dst_len); */
  /* if (0 > n)
     { */
  /*    fprintf(stderr, "! recvfrom: %s\n", strerror(errno)); */
  /*    goto clean_exit; */
  /* } */

 clean_exit:
  if (sfd)
    {
      close(sfd);
    }
  if (msg)
    {
      free(msg);
    }

#ifdef WINNT
  WSACleanup();
#endif
}

int
main(int argc, char* argv[])
{
  int ch;

  if (1 == argc)
    {
      usage(argv[0]);
      goto clean_exit;
    }


  while (-1 != (ch = getopt_long(argc, argv, "hs:p:q:", longopts, 0)))
    {
      switch (ch)
        {
        case 's':
          strcpy(opt_server, optarg);
          break;
        case 'p':
          opt_port = (uint16_t) atoi(optarg);
          break;
        case 'q':
          strcpy(opt_name, optarg);
          break;
        default:
          usage(argv[0]);
          goto clean_exit;
        }
    }

  printf("; <<>> dnsq <<>> -q%s -p%d @%s\n",
         opt_name,
         opt_port,
         opt_server);

  query();

 clean_exit:
  return 0;
}
