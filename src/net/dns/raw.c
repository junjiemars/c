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


/* type */
#define DNS_TYPE_A      0x01
#define DNS_TYPE_NS     0x02
#define DNS_TYPE_MD     0x03
#define DNS_TYPE_MF     0x04
#define DNS_TYPE_CNAME  0x05
#define DNS_TYPE_SOA    0x06
#define DNS_TYPE_MB     0x07
#define DNS_TYPE_MG     0x08
#define DNS_TYPE_MR     0x09
#define DNS_TYPE_NULL   0x0a
#define DNS_TYPE_WKS    0x0b
#define DNS_TYPE_PTR    0x0c
#define DNS_TYPE_HINFO  0x0d
#define DNS_TYPE_MX     0x0e
#define DNS_TYPE_TXT    0x0f

#define DNS_PTR_NAME    0xc0


/* class */
#define DNS_CLASS_IN  0x01
#define DNS_CLASS_CS  0x02
#define DNS_CLASS_CH  0x03
#define DNS_CLASS_HS  0x04


/* length */
#define DNS_QNAME_MAX_LEN  255
#define DNS_LABEL_MAX_LEN  64
#define DNS_UDP_MAX_LEN    512


#define dns_ptr_type(u16)    ((uint8_t)((uint16_t)ntohs(u16) >> 8))
#define dns_ptr_offset(u16)  ((uint8_t)((uint16_t)ntohs(u16) & 0xff))


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
  uint32_t type    : 16;
  uint32_t class   : 16;
} s_dns_qs;


/* resource record */
typedef struct s_dns_rr
{
  uint16_t name;
  uint16_t type;
  uint16_t class;
  uint32_t ttl;
  uint16_t rdlength;
} s_dns_rr;


static void query(void);
static void make_label(uint8_t *dst, size_t *dst_len, uint8_t *name);
static void parse_label(uint8_t *buf, uint8_t *offset, uint8_t *name,
                        size_t *name_len);
static int make_request(uint8_t **req, size_t *req_len, uint16_t *req_id);
static void parse_response(uint16_t id, uint8_t *res);
static void parse_rr(uint8_t *res, uint8_t **offset);
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
static struct timeval   opt_timeout        =  { .tv_sec = 15, 0 };
static char opt_query[DNS_QNAME_MAX_LEN]   =  { 0, };
static char opt_server[DNS_QNAME_MAX_LEN]  =  "127.0.0.53";

static char *dns_type_str[] = {
  0,
  "A",      "NS",    "MD",   "MF",
  "CNAME",  "SOA",   "MB",   "MG",
  "MR",     "NULL",  "WKS",  "PTR",
  "HINFO",  "MX",    "TXT",
  0
};

static char *dns_class_str[] = {
  0,
  "IN",     "CS",    "CH",   "HS",
  0
};


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
              *dst_len = dst - d + 1;
              break;
            }
        }

      p++;
    }
}


void
parse_label(uint8_t *buf, uint8_t *offset, uint8_t *name, size_t *name_len)
{
  uint8_t  *p, *d, len;

  p = offset;
  d = name;
  *name_len = 0;

  while (*name_len < DNS_QNAME_MAX_LEN)
    {
      if (DNS_PTR_NAME == dns_ptr_type(*(uint16_t *) p))
        {
          offset = buf + dns_ptr_offset(*(uint16_t *) p);
          p = offset;
          continue;
        }

      if (0 == *p)
        {
          *--d = 0;
          *name_len += 1;
          break;
        }

      len = *p;
      memcpy(d, p + 1, len);
      d += len;
      *d++ = '.';
      *name_len += 1 + len;
      p += 1 + len;
    }
}

int
make_request(uint8_t **req, size_t *req_len, uint16_t *req_id)
{
  s_dns_hs   hs;
  s_dns_qs   qs;
  uint8_t   *msg  =  0;
  uint8_t    qname[DNS_QNAME_MAX_LEN];
  size_t     qname_len = 0;

  /* make header */
  memset(&hs, 0, sizeof(hs));
  hs.id = htons(*req_id = getpid());
  hs.h_flags.rd = (uint8_t) htons(1u);
  hs.qdcount = htons(1u);

  /* make question */
  memset(&qs, 0, sizeof(qs));
  make_label(&qname[0], &qname_len, (uint8_t*) opt_query);
  qs.type = htons(DNS_TYPE_A);
  qs.class = htons(DNS_CLASS_IN);

  /* make message */
  *req_len = sizeof(s_dns_hs) + qname_len + sizeof(s_dns_qs);
  msg = calloc(1, *req_len);
  if (0 == msg)
    {
      fprintf(stderr, "!calloc: %s\n", strerror(errno));
      return -1;
    }
  memcpy(msg, &hs, sizeof(hs));
  memcpy(msg + sizeof(hs), qname, qname_len);
  memcpy(msg + sizeof(hs) + qname_len, &qs, sizeof(qs));

  *req = msg;
  return 0;
}

void
parse_rr(uint8_t *res, uint8_t **offset)
{
  s_dns_rr  *rr;
  uint8_t    qname[DNS_QNAME_MAX_LEN];
  size_t     qname_len  =  0;

  rr = (s_dns_rr *) *offset;
  if (DNS_PTR_NAME == dns_ptr_type(rr->name))
    {
      parse_label(res, res + dns_ptr_offset(rr->name), qname, &qname_len);
    }

  fprintf(stdout, " -> %s  %s  %s  %d",
          qname,
          dns_type_str[ntohs(rr->type)],
          dns_class_str[ntohs(rr->class)],
          ntohl(rr->ttl));
      
  *offset += sizeof(*rr);

  if (ntohs(rr->rdlength) > 0)
    {
      switch (ntohs(rr->type))
        {
        case DNS_TYPE_CNAME:
          parse_label(res, *offset, qname, &qname_len);
          fprintf(stdout, "  %s", qname);
          break;
        case DNS_TYPE_A:
          fprintf(stdout, "  %d.%d.%d.%d",
                  (*offset)[0], (*offset)[1], (*offset)[2], (*offset)[3]);
          break;
        default:
          break;
        }
    }
  fprintf(stdout, "\n");

  *offset += ntohs(rr->rdlength);
}

void
parse_response(uint16_t id, uint8_t *res)
{
  s_dns_hs  *hs;
  s_dns_qs  *qs;
  ssize_t    n;
  uint8_t    qname[DNS_QNAME_MAX_LEN];
  size_t     qname_len;
  uint8_t   *offset;

  hs = (s_dns_hs *) res;

  if (id != ntohs(hs->id))
    {
      fprintf(stderr, "!response: id is unmatched\n");
      return;
    }

  if (1 != hs->h_flags.qr)
    {
      fprintf(stderr, "!response: qr is not response\n");
      return;
    }

  n = (ssize_t) ntohs(hs->qdcount);
  offset = res + sizeof(*hs);
  fprintf(stdout, "# question section: %zu\n", (size_t) n);
  while (n-- > 0)
    {
      parse_label(res, offset, qname, &qname_len);
      offset += qname_len;
      qs = (s_dns_qs *) offset;

      fprintf(stdout, " -> %s  %s  %s\n",
              qname,
              dns_type_str[ntohs(qs->type)],
              dns_class_str[ntohs(qs->class)]);
      offset += sizeof(*qs);
    }

  n = (ssize_t) ntohs(hs->ancount);
  fprintf(stdout, "# answer section: %zu\n", (size_t) n);
  while (n-- > 0)
    {
      parse_rr(res, &offset);
    }

  /* n = (ssize_t) ntohs(hs->arcount); */
  /* fprintf(stdout, "# additional section: %zu\n", (size_t) n); */
  /* while (n-- > 0) */
  /*   { */
  /*     rr = (s_dns_rr *) offset; */
  /*     if (DNS_PTR_NAME == dns_ptr_type(rr->name)) */
  /*       { */
  /*         parse_label(res, res + dns_ptr_offset(rr->name), qname, &qname_len); */
  /*       } */
  /*     fprintf(stdout, " -> %s  %s  %s  %d\n", */
  /*             qname, */
  /*             dns_type_str[ntohs(rr->type)], */
  /*             dns_class_str[ntohs(rr->class)], */
  /*             ntohl(rr->ttl)); */
  /*     offset += sizeof(*rr) + ntohs(rr->rdlength); */
  /*   } */
}

void
query(void)
{
  int                  rc;
  sockfd_t             sfd  =  0;
  uint8_t             *req  =  0;
  size_t               req_len;
  uint16_t             req_id;
  uint8_t             *res  =  0;
  struct in_addr       host;
  struct sockaddr_in   dst;
  socklen_t            dst_len;
  ssize_t              n;

#if (WINNT)
  WSADATA wsa;
  rc= WSAStartup(MAKEWORD(2, 2), &wsa);
  if (rc)
    {
      fprintf(stderr, "!WSAStartup failed\n");
      goto clean_exit;
    }
#endif

  rc = make_request(&req, &req_len, &req_id);
  if (-1 == rc)
    {
      fprintf(stderr, "!make_request: failed\n");
      goto clean_exit;
    }

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
      dump(req, req_len, opt_dump_req);
    }

  rc = setsockopt(sfd, SOL_SOCKET, SO_SNDTIMEO, &opt_timeout,
                  sizeof(opt_timeout));
  if (-1 == rc)
    {
      fprintf(stderr, "!setsockopt: SO_SNDTIMEO %s\n", strerror(errno));
    }

  n = sendto(sfd, req, req_len, 0, (const struct sockaddr*) &dst, dst_len);
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
      fprintf(stderr, "!setsockopt: SO_RCVTIMEO %s\n", strerror(errno));
    }

  res = calloc(1, DNS_UDP_MAX_LEN);
  if (!res)
    {
      fprintf(stderr, "!calloc: %s\n", strerror(errno));
      goto clean_exit;
    }

  rc = recvfrom(sfd, res, DNS_UDP_MAX_LEN, 0, (struct sockaddr *) &dst,
                &dst_len);
  if (-1 == rc)
    {
      fprintf(stderr, "!recvfrom: %s\n", strerror(errno));
      goto clean_exit;
    }

  if (opt_dump)
    {
      dump(req, req_len, opt_dump_res);
    }

  parse_response(req_id, res);

 clean_exit:
  if (sfd)
    {
      close(sfd);
    }
  free(res);
  free(req);

#if (WINNT)
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

  printf("# command line options:\n -> -q%s -s%s -p%d -t%d -d%d\n",
         opt_query,
         opt_server,
         opt_port,
         (int) opt_timeout.tv_sec,
         opt_dump);

  query();

 clean_exit:
  return 0;
}
