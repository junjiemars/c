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


#define DNS_TYPE_A     0x01
#define DNS_TYPE_NS    0x02
#define DNS_TYPE_MD    0x03
#define DNS_TYPE_PTR   0xc0

#define DNS_CLASS_IN   0x0001
#define DNS_CLASS_CS   0x0002
#define DNS_CLASS_CH   0x0003
#define DNS_CLASS_HS   0x0004

#define DNS_QNAME_MAX_LEN    255
#define DNS_LABEL_MAX_LEN    64
#define DNS_UDP_MAX_LEN  512


/* header section */
typedef struct s_dns_hs
{
  uint16_t id;
  struct h_flags
  {
#if (NM_HAVE_LITTLE_ENDIAN)
    uint8_t rcode  : 4;
    uint8_t z      : 3;
    uint8_t ra     : 1;
    uint8_t rd     : 1;
    uint8_t tc     : 1;
    uint8_t aa     : 1;
    uint8_t opcode : 4;
    uint8_t qr     : 1;
#else
    uint8_t qr     : 1;
    uint8_t opcode : 4;
    uint8_t aa     : 1;
    uint8_t tc     : 1;
    uint8_t rd     : 1;
    uint8_t ra     : 1;
    uint8_t z      : 3;
    uint8_t rcode  : 4;
#endif  /* NM_HAVE_LITTLE_ENDIAN */
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
  struct r_name
  {
    uint8_t type   : 8;
    uint8_t offset : 8;
  } name;
  uint16_t type;
  uint16_t class;
  uint16_t ttl;
  uint16_t rdlength;
  uint16_t rdata;
} s_dns_rr;

static void query(void);
static void make_label(uint8_t *dst, size_t *dst_len, uint8_t *name);
static void parse_label(uint8_t *buf, uint8_t *name, size_t *n);
static void dump(uint8_t *buf, size_t n, const char *where);


static struct option longopts[]  =
  {
    { "help",    no_argument,          0,              'h' },
    { "server",  optional_argument,    0,              's' },
    { "port",    optional_argument,    0,              'p' },
    { "query",   required_argument,    0,              'q' },
    { "timeout", optional_argument,    0,              't' },
    { "dump",    no_argument,          0,              'd' },
    { 0,         0,                    0,               0  }
  };

static int              opt_dump           =  0;
static char            *opt_dump_req       =  ".request";
static char            *opt_dump_res       =  ".response";
static uint16_t         opt_port           =  53;
static struct timeval   opt_timeout        =  { .tv_sec = 3, };
static char opt_query[DNS_QNAME_MAX_LEN]   =  { 0, };
static char opt_server[DNS_QNAME_MAX_LEN]  =  "127.0.0.53";


static void
usage(const char *p)
{
  printf("Usage %s [options ...] host\n", p);
  printf("  -h, --help     this help text\n");
  printf("  -s  --server   DNS server, default is %s\n",
         opt_server);
  printf("  -p, --port     query a non-standard port, default is %d\n",
         opt_port);
  printf("  -q, --query    the domain name to query\n");
  printf("  -t, --timeout  timeout in seconds, default is %d\n",
         (int) opt_timeout.tv_sec);
  printf("  -d, --dump     whether dump network package, default is %s\n",
         opt_dump ? "true" : "false");
}


void
make_label(uint8_t *dst, size_t *dst_len, uint8_t *name)
{
  uint8_t  *p, **pre, len, *d;

  p = name;
  pre = &name;
  d = dst;

  while ((p - name) < DNS_QNAME_MAX_LEN)
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
  *dst_len = dst - d + 1;
}


void
parse_label(uint8_t *buf, uint8_t *name, size_t *n)
{
  uint8_t  *p, len, *d;
  
  p = buf;
  d = name;
  *n = 0;

  while ((0 != *p) && (p - buf) < DNS_QNAME_MAX_LEN)
    {
      len = *p;
      memcpy(d, p + 1, len);
      d += len;
      *d++ = '.';
      *n = *n + 1 + len;
      p += 1 + len;
    }
  *--d = 0;
}

void
query(void)
{
  int                  rc;
  s_dns_hs             header;
  uint8_t              qname[DNS_QNAME_MAX_LEN];
  size_t               qname_len;
  s_dns_qs             question;
  sockfd_t             sfd;
  uint8_t             *msg;
  size_t               msg_len;
  struct in_addr       host;
  struct sockaddr_in   dst;
  socklen_t            dst_len;
  ssize_t              n;
  uint8_t             *offset;
  s_dns_rr            *rr;

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
  header.h_flags.rd = htons(1u);
  header.qdcount = htons(1u);

  /* make question */
  memset(&question, 0, sizeof(question));
  make_label(qname, &qname_len, (uint8_t*) opt_query);
  question.qtype = htons(DNS_TYPE_A);
  question.qclass = htons(DNS_CLASS_IN);

  /* make message */
  msg_len = sizeof(s_dns_hs) + qname_len + sizeof(s_dns_qs);
  msg = malloc(DNS_UDP_MAX_LEN);
  if (0 == msg)
    {
      fprintf(stderr, "!malloc: %s\n", strerror(errno));
      goto clean_exit;
    }
  memset(msg, 0, DNS_UDP_MAX_LEN);
  memcpy(msg, &header, sizeof(header));
  memcpy(msg + sizeof(header), qname, qname_len);
  memcpy(msg + sizeof(header) + qname_len, &question, sizeof(question));

  /* socket */
  sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (-1 == sfd)
    {
      fprintf(stderr, "!socket: %s\n", strerror(errno));
      goto clean_exit;
    }

  rc = inet_pton(AF_INET, opt_server, &host);
  if (-1 == rc)
    {
      fprintf(stderr, "!inet_pton: %s\n", strerror(errno));
      goto clean_exit;
    }

  /* send */
  dst_len = sizeof(dst);
  memset(&dst, 0, sizeof(dst));
  dst.sin_family = AF_INET;
  dst.sin_port = htons(opt_port);
  dst.sin_addr = host;

  if (opt_dump)
    {
      dump(msg, msg_len, opt_dump_req);
    }

  n = sendto(sfd, msg, msg_len, 0, (const struct sockaddr*) &dst, dst_len);
  if (-1 == n)
    {
      fprintf(stderr, "!sendto: %s\n", strerror(errno));
      goto clean_exit;
    }

  /* receive */
  rc = setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, &opt_timeout,
                  sizeof(opt_timeout));
  if (-1 == rc)
    {
      fprintf(stderr, "!setsockopt: %s\n", strerror(errno));
      goto clean_exit;
    }
  memset(msg, 0, DNS_UDP_MAX_LEN);

  rc = recvfrom(sfd, msg, DNS_UDP_MAX_LEN, 0, (struct sockaddr *) &dst,
                &dst_len);
  if (-1 == rc)
    {
      fprintf(stderr, "!recvfrom: %s\n", strerror(errno));
      goto clean_exit;
    }
  msg_len = rc;

  if (opt_dump)
    {
      dump(msg, msg_len, opt_dump_res);
    }

  if (header.id != ((s_dns_hs *) msg)->id)
    {
      fprintf(stderr, "!response: id is %d unmatched\n", ntohs(header.id));
      goto clean_exit;
    }
  if (1 != ((s_dns_hs *) msg)->h_flags.qr)
    {
      fprintf(stderr, "!response: qr is not response\n");
      goto clean_exit;
    }


  n = ntohs(((s_dns_hs*) msg)->ancount);
  offset = msg + sizeof(s_dns_hs) + qname_len + sizeof(s_dns_qs);
  while (n-- > 0)
    {
      rr = (s_dns_rr *) offset;
      if (DNS_TYPE_PTR == rr->name.type)
        {
          parse_label(msg + rr->name.offset, qname, &qname_len);
        }
      fprintf(stdout, "# %s\n", qname);

      offset += sizeof(s_dns_rr);
    }

 clean_exit:
  if (sfd)
    {
      close(sfd);
    }
  free(msg);

#ifdef WINNT
  WSACleanup();
#endif
}


void
dump(uint8_t *b, size_t n, const char *w)
{
  FILE    *f;
  size_t   len;

  f = fopen(w, "wb");
  if (!f)
    {
      fprintf(stderr, "!fopen: %s\n", strerror(errno));
      return;
    }

  len = fwrite(b, 1, n, f);
  if (ferror(f))
    {
      fprintf(stderr, "!fwrite: %s\n", strerror(errno));
      clearerr(f);
      goto clean_exit;
    }
  if (len < n)
    {
       fprintf(stderr, "!fwrite: %zu/%zu\n", len, n);
       goto clean_exit;
    }

 clean_exit:
  fclose(f);
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


  while (-1 != (ch = getopt_long(argc, argv, "hs:p:q:t:d", longopts, 0)))
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
          strcpy(opt_query, optarg);
          break;
        case 't':
          opt_timeout.tv_sec = atoi(optarg);
          break;
        case 'd':
          opt_dump = 1;
          break;
        default:
          usage(argv[0]);
          goto clean_exit;
        }
    }

  printf("# -q%s -p%d -s%s -t%d -d%d\n",
         opt_query,
         opt_port,
         opt_server,
         (int) opt_timeout.tv_sec,
         opt_dump);

  query();

 clean_exit:
  return 0;
}
