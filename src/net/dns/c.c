#include "_net_.h"
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#if !(NDEBUG)
#include <signal.h>
#endif  /* NDEBUG */


/*
 * References:
 * 1. https://datatracker.ietf.org/doc/html/rfc1034
 * 2. https://datatracker.ietf.org/doc/html/rfc1035
 *
 */


/* type */
#define DNS_TYPE_MAP(XX)                        \
  XX(0x01, A)                                   \
  XX(0x02, NS)                                  \
  XX(0x03, MD)                                  \
  XX(0x04, MF)                                  \
  XX(0x05, CNAME)                               \
  XX(0x06, SOA)                                 \
  XX(0x07, MB)                                  \
  XX(0x08, MG)                                  \
  XX(0x09, MR)                                  \
  XX(0x0a, NULL)                                \
  XX(0x0b, WKS)                                 \
  XX(0x0c, PTR)                                 \
  XX(0x0d, HINFO)                               \
  XX(0x0e, MX)                                  \
  XX(0x0f, TXT)                                 \
  
enum dns_type
  {
#define XX(n, s) DNS_TYPE_##s = n,
    DNS_TYPE_MAP(XX)
#undef XX
  };


/* class */
#define DNS_CLASS_MAP(XX)                       \
  XX(1, IN)                                     \
  XX(2, CS)                                     \
  XX(3, CH)                                     \
  XX(4, HS)                                     \

enum dns_class
  {
#define XX(n, s) DNS_CLASS_##s = n,
    DNS_CLASS_MAP(XX)
#undef XX
  };

#define DNS_PTR_NAME    0xc0

/* length */
#define DNS_QNAME_MAX_LEN  255
#define DNS_LABEL_MAX_LEN  64
#define DNS_UDP_MAX_LEN    512


#define dns_ptr_type(u16)    ((ntohs((uint16_t)u16) >> 8) & 0xff)
#define dns_ptr_offset(u16)  ((ntohs((uint16_t)u16)) & 0xff)

#define tr_dns_type_str(n)                            \
  ((size_t)(n-1) < countof(dns_type_str)              \
   ? dns_type_str[(size_t)(n-1)] : dns_type_str[0])


#define tr_dns_class_str(n)                           \
  ((size_t)(n-1) < countof(dns_class_str)             \
   ? dns_class_str[(size_t)(n-1)] : dns_class_str[0])


#define tr_dns_flags_str(a, n)                                \
  ((size_t)(n) < countof(a) ? a[(size_t)(n)] : ";; invalid")


#define log(x, ...)                             \
  if (0 == opt_quiet)                           \
    {                                           \
      fprintf(x, __VA_ARGS__);                  \
    }


/* header section */
#pragma pack(push, 1)
typedef struct s_dns_hs
{
  uint16_t id;
  struct flags
  {
#if (NM_HAVE_LITTLE_ENDIAN)
    uint16_t rcode  : 4;
    uint16_t z      : 3;
    uint16_t ra     : 1;
    uint16_t rd     : 1;
    uint16_t tc     : 1;
    uint16_t aa     : 1;
    uint16_t opcode : 4;
    uint16_t qr     : 1;
#else
    uint16_t qr     : 1;
    uint16_t opcode : 4;
    uint16_t aa     : 1;
    uint16_t tc     : 1;
    uint16_t rd     : 1;
    uint16_t ra     : 1;
    uint16_t z      : 3;
    uint16_t rcode  : 4;
#endif  /* NM_HAVE_LITTLE_ENDIAN */
  } flags;
  uint16_t qdcount;
  uint16_t ancount;
  uint16_t nscount;
  uint16_t arcount;
} s_dns_hs;
#pragma pack(pop)


/* question section */
#pragma pack(push, 1)
typedef struct s_dns_qs
{
  uint32_t type    : 16;
  uint32_t class   : 16;
} s_dns_qs;
#pragma pack(pop)


/* resource record */
#pragma pack(push, 1)
typedef struct s_dns_rr
{
  uint16_t  name;
  uint16_t  type;
  uint16_t  class;
  int32_t   ttl;
  uint16_t  rdlength;
} s_dns_rr;
#pragma pack(pop)


#if !(NDEBUG)
typedef void (*on_signal)(int);
static void on_signal_segv(int sig);
#endif  /* NDEBUG */

static void query(void);
static void make_label(uint8_t *dst, size_t *dst_len, uint8_t *name);
static void parse_label(uint8_t *buf, uint8_t *offset, uint8_t *name,
                        size_t *name_len);
static int make_request(uint8_t **req, size_t *req_len, uint16_t *req_id);
static void parse_response(uint16_t id, uint8_t *res);
static int parse_rr(uint8_t *res, uint8_t **offset);
static void out(uint8_t *buf, size_t n, const char *where);
static void in(const char *where);


static struct option longopts[]  =
  {
    { "help",    no_argument,          0,              'h' },
    { "query",   required_argument,    0,              'q' },
    { "server",  optional_argument,    0,              's' },
    { "port",    optional_argument,    0,              'p' },
    { "type",    optional_argument,    0,              't' },
    { "retry",   optional_argument,    0,              'r' },
    { "timeout", optional_argument,    0,              'T' },
    { "out",     optional_argument,    0,              'o' },
    { "in",      required_argument,    0,              'i' },
    { "quiet",   no_argument,          0,              'Q' },
    { 0,         0,                    0,               0  }
  };


static uint16_t        opt_port            =  53;
static int             opt_type            =  DNS_TYPE_A;
static char            opt_type_str[8]     =  { 0, };
static uint8_t         opt_retry           =  1;
static struct timeval  opt_timeout         =  { .tv_sec = 15, 0 };
static int             opt_quiet           =  0;
static int             opt_out             =  0;
static int             opt_in              =  0;
static char opt_file[DNS_QNAME_MAX_LEN]    =  ".response";
static char opt_query[DNS_QNAME_MAX_LEN]   =  { 0, };
static char opt_server[DNS_QNAME_MAX_LEN]  =  "127.0.0.53";


static char *dns_type_str[] = {
#define XX(n, s) #s,
  DNS_TYPE_MAP(XX)
#undef XX
};

static char *dns_class_str[] = {
#define XX(n, s) #s,
  DNS_CLASS_MAP(XX)
#undef XX
};

static char *dns_qr_str[] = {
  ";; a query",
  ";; a response",
};

static char *dns_aa_str[] = {
  ";; not authoritative answer",
  ";; authoritative answer",
};

static char *dns_tc_str[] = {
  ";; not truncated",
  ";; trucated",
};

static char *dns_opcode_str[] = {
  ";; a standard query",
  ";; an inverse query",
  ";; a server status request",
  ";; reserved",
};

static char *dns_rcode_str[] = {
  ";; no error condition",
  ";; format error",
  ";; server failure",
  ";; name error",
  ";; not implemented",
  ";; refused",
};

static void
usage(const char *p)
{
  printf("Usage %s [options ...]\n", p);
  printf("  -h, --help     this help text\n");
  printf("  -q, --query    the domain name to query\n");
  printf("  -t, --type     query type, default is %s\n",
         tr_dns_type_str(opt_type));
  printf("  -s  --server   DNS server, default is %s\n",
         opt_server);
  printf("  -p, --port     query a non-standard port, default is %d\n",
         opt_port);
  printf("  -r, --retry    retry times after failed, default is %d\n",
         opt_retry);
  printf("  -T, --timeout  timeout in seconds, default is %d\n",
         (int) opt_timeout.tv_sec);
  printf("  -o, --out      out response to [%s|<file>]\n", opt_file);
  printf("  -i, --in       parse response from [%s|<file>]\n", opt_file);
  printf("  -Q, --quiet    quiet or silent mode\n");
}


void
query(void)
{
  int                  rc;
  sockfd_t             sfd      =  0;
  uint8_t             *req      =  0;
  size_t               req_len;
  uint16_t             req_id;
  uint8_t             *res      =  0;
  size_t               res_len  =  0;
  struct in_addr       host;
  struct sockaddr_in   dst;
  socklen_t            dst_len;
  uint8_t              retry;

#if (WINNT)
  WSADATA wsa;
  rc = WSAStartup(MAKEWORD(2, 2), &wsa);
  if (rc)
    {
      log(stderr, "! WSAStartup: %s\n", strerror(errno));
      goto clean_exit;
    }
#endif  /* WINNT */

  rc = make_request(&req, &req_len, &req_id);
  if (-1 == rc)
    {
      log(stderr, "! make_request: failed\n");
      goto clean_exit;
    }

  /* socket */
  sfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if (-1 == sfd)
    {
      log_sock_err("! socket: %s\n");
      goto clean_exit;
    }

  rc = inet_pton(AF_INET, opt_server, &host);
  if (-1 == rc)
    {
      log_sock_err("! inet_pton: %s\n");
      goto close_exit;
    }

  /* send */
  dst_len = sizeof(dst);
  memset(&dst, 0, sizeof(dst));
  dst.sin_family = AF_INET;
  dst.sin_port = htons(opt_port);
  dst.sin_addr = host;

#if (LINUX)
  rc = setsockopt(sfd, SOL_SOCKET, SO_SNDTIMEO, &opt_timeout,
                  sizeof(opt_timeout));
  if (-1 == rc)
    {
      log_sock_err("! setsockopt: SO_SNDTIMEO %s\n");
    }
#endif

  retry = opt_retry;
  while (retry-- > 0)
    {
      rc = __sendto(sfd, req, req_len, 0, &dst, dst_len);
      if (-1 == rc)
        {
          log_sock_err("! sendto: %s\n");
          continue;
        }
      break;
    }
  if (-1 == rc)
    {
      goto close_exit;
    }

  /* receive */
#if (LINUX)
  rc = setsockopt(sfd, SOL_SOCKET, SO_RCVTIMEO, &opt_timeout,
                  sizeof(opt_timeout));
  if (-1 == rc)
    {
      log_sock_err("! setsockopt: SO_RCVTIMEO %s\n");
    }
#endif

  res = calloc(1, DNS_UDP_MAX_LEN);
  if (!res)
    {
      log(stderr, "! calloc: %s\n", strerror(errno));
      goto close_exit;
    }

  retry = opt_retry;
  res_len = DNS_UDP_MAX_LEN;
  while (retry-- > 0)
    {
      rc = __recvfrom(sfd, res, res_len, 0, &dst, &dst_len);
      if (-1 == rc)
        {
          log_sock_err("! recvfrom: %s\n");
          continue;
        }
      res_len = rc;
      break;
    }
  if (-1 == rc)
    {
      goto close_exit;
    }
  out(res, res_len, opt_file);
  log(stdout, "# message size: %zu bytes\n", res_len);

  parse_response(req_id, res);

 close_exit:
  close(sfd);
 clean_exit:
  free(res);
  free(req);

#if (WINNT)
  WSACleanup();
#endif  /* WINNT */
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
  uint8_t   *p, *d, len;
  uint16_t   ptr;
  size_t     n;

  p = offset;
  d = name;
  n = 0;

  while (n < DNS_QNAME_MAX_LEN)
    {
      ptr = *(uint16_t *) p;
      if (DNS_PTR_NAME == dns_ptr_type(ptr))
        {
          p = buf + dns_ptr_offset(ptr);
          continue;
        }

      if (0 == *p)
        {
          *--d = 0;
          ++n;
          break;
        }

      len = *p++;
      memcpy(&d[0], &p[0], len);
      d += len;
      *d++ = (uint8_t) '.';
      n += 1 + len;
      p += len;
    }

  *name_len = n;
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
  hs.flags.rd = (uint8_t) htons(1u);
  hs.qdcount = htons(1u);

  /* make question */
  memset(&qs, 0, sizeof(qs));
  make_label(&qname[0], &qname_len, (uint8_t*) opt_query);
  qs.type = htons(opt_type);
  qs.class = htons(DNS_CLASS_IN);

  /* make message */
  *req_len = sizeof(s_dns_hs) + qname_len + sizeof(s_dns_qs);
  msg = calloc(1, *req_len);
  if (0 == msg)
    {
      log(stderr, "! calloc: %s\n", strerror(errno));
      return -1;
    }
  memcpy(msg, &hs, sizeof(hs));
  memcpy(msg + sizeof(hs), qname, qname_len);
  memcpy(msg + sizeof(hs) + qname_len, &qs, sizeof(qs));

  *req = msg;
  return 0;
}


int
parse_rr(uint8_t *res, uint8_t **offset)
{
  s_dns_rr    *rr                        =  0;
  uint16_t     rdlength                  =  0;
  size_t       qname_len                 =  0;
  uint8_t      qname[DNS_QNAME_MAX_LEN]  =  {0};

  rr = (s_dns_rr *) *offset;
  if (DNS_PTR_NAME == dns_ptr_type(rr->name))
    {
      parse_label(res, res + dns_ptr_offset(rr->name), qname, &qname_len);
    }
  rdlength = ntohs(rr->rdlength);
  *offset += sizeof(*rr);

  log(stdout, " -> %s  %s  %s  %i  %u", qname,
      tr_dns_type_str(ntohs(rr->type)),
      tr_dns_class_str(ntohs(rr->class)),
      (int) ntohl(rr->ttl), rdlength);

  if (0 == rdlength)
    {
      log(stdout, "\n");
      return 0;
    }

  log(stdout, "  ");
  switch (ntohs(rr->type))
    {
    case DNS_TYPE_CNAME:
      qname_len = 0;
      qname[0] = 0;
      parse_label(res, (uint8_t *) &rr->name, qname, &qname_len);
      if (qname_len == 0)
        {
          qname[0] = 0;
        }
      fprintf(stdout, "%s%c", (const char *) qname, opt_quiet ? '\n' : 0);
      break;
    case DNS_TYPE_A:
      fprintf(stdout, "%u.%u.%u.%u%c", (*offset)[0], (*offset)[1],
              (*offset)[2], (*offset)[3], opt_quiet ? '\n' : 0);
      break;
    default:
      break;
    }
  log(stdout, "\n");

  *offset += rdlength;
  return (int) rdlength;
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
  log(stdout, "# header section:\n");

  log(stdout, " -> ID  %u  <- %u\n", ntohs(hs->id), id);

  log(stdout, " -> QR  %u  %s\n", hs->flags.qr,
      tr_dns_flags_str(dns_qr_str, hs->flags.qr));

  log(stdout, " -> AA  %u  %s\n", hs->flags.aa,
      tr_dns_flags_str(dns_aa_str, hs->flags.aa));

  log(stdout, " -> TC  %u  %s\n", hs->flags.tc,
      tr_dns_flags_str(dns_tc_str, hs->flags.tc));

  log(stdout, " -> OPCODE  %u  %s\n", hs->flags.opcode,
      tr_dns_flags_str(dns_opcode_str, hs->flags.opcode));

  log(stdout, " -> RCODE  %u  %s\n", hs->flags.rcode,
      tr_dns_flags_str(dns_rcode_str, hs->flags.rcode));

  n = (ssize_t) ntohs(hs->qdcount);
  offset = res + sizeof(*hs);
  log(stdout, "# question section: %zu\n", (size_t) n);
  while (n-- > 0)
    {
      qname_len = 0;
      parse_label(res, offset, qname, &qname_len);
      if (qname_len == 0)
        {
          qname[0] = 0;
        }
      offset += qname_len;
      qs = (s_dns_qs *) offset;

      log(stdout, " -> %s  %s  %s\n", qname,
          tr_dns_type_str(ntohs(qs->type)),
          tr_dns_class_str(ntohs(qs->class)));

      offset += sizeof(*qs);
    }

  n = (ssize_t) ntohs(hs->ancount);
  log(stdout, "# answer section: %zu\n", (size_t) n);
  while (n-- > 0)
    {
      if (0 == parse_rr(res, &offset))
        {
          continue;
        }
    }

  n = (ssize_t) ntohs(hs->nscount);
  log(stdout, "# authority section: %zu\n", (size_t) n);
  while (n-- > 0)
    {
      if (0 == parse_rr(res, &offset))
        {
          continue;
        }
    }

  n = (ssize_t) ntohs(hs->arcount);
  log(stdout, "# additional section: %zu\n", (size_t) n);
  while (n-- > 0)
    {
      if (0 == parse_rr(res, &offset))
        {
          continue;
        }
    }
}


void
out(uint8_t *b, size_t n, const char *w)
{
  FILE    *f;
  size_t   len;

  if (!opt_out)
    {
      return;
    }

  f = fopen(w, "wb");
  if (!f)
    {
      log(stderr, "! fopen: %s\n", strerror(errno));
      return;
    }

  len = fwrite(b, 1, n, f);
  if (ferror(f))
    {
      log(stderr, "! fwrite: %s\n", strerror(errno));
      clearerr(f);
      goto clean_exit;
    }
  if (len < n)
    {
      log(stderr, "! fwrite: %zu/%zu\n", len, n);
      goto clean_exit;
    }

 clean_exit:
  fclose(f);
}

void
in(const char *w)
{
  FILE     *f;
  size_t    n;
  uint8_t   b[DNS_UDP_MAX_LEN];

  f = fopen(w, "rb");
  if (!f)
    {
      log(stderr, "! fopen: %s\n", strerror(errno));
      return;
    }

  n = fread(b, 1, DNS_UDP_MAX_LEN, f);
  if (ferror(f))
    {
      log(stderr, "! fread: %s\n", strerror(errno));
      clearerr(f);
      goto clean_exit;
    }
  if (n == 0)
    {
      goto clean_exit;
    }

  parse_response((uint16_t) 0, &b[0]);

 clean_exit:
  fclose(f);
}

#if !(NDEBUG)
void
on_signal_segv(int sig)
{
  log(stderr, "!%s: %d\n", __FUNCTION__, sig);
  exit(EXIT_FAILURE);
}
#endif  /* NDEBUG */


int
main(int argc, char* argv[])
{
  int  ch, i;

  if (1 == argc)
    {
      usage(argv[0]);
      goto clean_exit;
    }

#if !(NDEBUG)
  on_signal  on_segv;
  on_segv = signal(SIGSEGV, on_signal_segv);
  if (SIG_ERR == on_segv)
    {
      log(stderr, "! signal: %s\n", strerror(errno));
      goto clean_exit;
    }
#endif  /* NDEBUG */

  while (-1 != (ch = getopt_long(argc, argv,
                                 "hs:p:q:t:r:T:oi:Q",
                                 longopts, 0)))
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
        case 'r':
          opt_retry = atoi(optarg);
          break;
        case 't':
          for (i = 0; i < (int) countof(dns_type_str); i++)
            {
              if (0 == strcmp(dns_type_str[i], optarg))
                {
                  opt_type = (uint16_t) (i + 1);
                  strcpy(opt_type_str, optarg);
                  break;
                }
            }
          if (i == countof(dns_type_str))
            {
              fprintf(stderr, "! invalid argument: --type=%s\n", optarg);
              usage(argv[0]);
              goto clean_exit;
            }
          break;
        case 'T':
          opt_timeout.tv_sec = atoi(optarg);
          break;
        case 'o':
          opt_out = 1;
          if (optarg)
            {
              strcpy(opt_file, optarg);
            }
          break;
        case 'i':
          opt_in = 1;
          strcpy(opt_file, optarg);
          break;
        case 'Q':
          opt_quiet = 1;
          break;
        default:
          usage(argv[0]);
          goto clean_exit;
        }
    }

  opt_quiet %= 3;

  if (opt_in)
    {
      log(stdout, "# command line options:\n"
          " -> --in=%s --quiet=%d\n",
          opt_file,
          opt_quiet);
      in(opt_file);
    }
  else
    {
      log(stdout, "# command line options:\n"
          " -> --query=%s --server=%s --port=%d --type=%s\n"
          " -> --retry=%d --timeout=%d --out=%s --quiet=%d\n",
          opt_query,
          opt_server,
          opt_port,
          tr_dns_type_str(opt_type),
          (int) opt_retry,
          (int) opt_timeout.tv_sec,
          opt_out ? opt_file : "",
          opt_quiet);
      query();
    }

 clean_exit:
  return 0;
}


/* eof */
