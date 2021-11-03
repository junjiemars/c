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


#define dns_ptr_type(u16)    ((ntohs((uint16_t)u16) >> 8) & 0xff)
#define dns_ptr_offset(u16)  ((ntohs((uint16_t)u16)) & 0xff)

#define tr_dns_str(a, i, t, tr)                         \
  (a[((t)(tr(i)+1)) >= (t)countof(a) ? (countof(a)-1) : tr(i)])


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
#pragma pack(push, 1)
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
    { "server",  optional_argument,    0,              's' },
    { "port",    optional_argument,    0,              'p' },
    { "query",   required_argument,    0,              'q' },
    { "retry",   optional_argument,    0,              'r' },
    { "timeout", optional_argument,    0,              't' },
    { "out",     optional_argument,    0,              'o' },
    { "in",      required_argument,    0,              'i' },
    { "verbose", optional_argument,    0,              'v' },
    { 0,         0,                    0,               0  }
  };


static uint16_t        opt_port            =  53;
static uint8_t         opt_retry           =  1;
static struct timeval  opt_timeout         =  { .tv_sec = 15, 0 };
static int             opt_verbose         =  1;
static int             opt_out             =  0;
static int             opt_in              =  0;
static char opt_file[DNS_QNAME_MAX_LEN]    =  ".response";
static char opt_query[DNS_QNAME_MAX_LEN]   =  { 0, };
static char opt_server[DNS_QNAME_MAX_LEN]  =  "127.0.0.53";

static char *dns_type_str[] = {
  0,
  "A",      "NS",    "MD",   "MF",
  "CNAME",  "SOA",   "MB",   "MG",
  "MR",     "NULL",  "WKS",  "PTR",
  "HINFO",  "MX",    "TXT",
  ";; error, TYPE in [1,15]"
};

static char *dns_class_str[] = {
  0,
  "IN",     "CS",    "CH",   "HS",
  ";; error, CLASS in [1,4]"
};

static char *dns_qr_str[] = {
  ";; a query",
  ";; a response",
  ";; error, QR should in [0,1]"
};

static char *dns_aa_str[] = {
  ";; not authoritative answer",
  ";; authoritative answer",
  ";; error, AA should in [0,1]"
};

static char *dns_tc_str[] = {
  ";; not truncated",
  ";; trucated",
  ";; error, TC should in [0,1]"
};

static char *dns_opcode_str[] = {
  ";; a standard query",
  ";; an inverse query",
  ";; a server status request",
  ";; reserved",
  ";; error, OPCODE should in [0,3]"
};

static char *dns_rcode_str[] = {
  ";; no error condition",
  ";; format error",
  ";; server failure",
  ";; name error",
  ";; not implemented",
  ";; refused",
  ";; error, RCODE should in [0,5]"
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
  printf("  -r, --retry    retry times after failed, default is %d\n",
         opt_retry);
  printf("  -t, --timeout  timeout in seconds, default is %d\n",
         (int) opt_timeout.tv_sec);
  printf("  -o, --out      out response to [%s|file], default is %d\n",
         opt_file, opt_out);
  printf("  -i, --in       parse response from [%s|file], default is %d\n",
         opt_file, opt_in);
  printf("  -v, --verbose  verbose output, default is %d\n", opt_verbose);
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
      fprintf(stderr, "! WSAStartup: %s\n", strerror(errno));
      goto clean_exit;
    }
#endif  /* WINNT */

  rc = make_request(&req, &req_len, &req_id);
  if (-1 == rc)
    {
      fprintf(stderr, "! make_request: failed\n");
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
      fprintf(stderr, "! calloc: %s\n", strerror(errno));
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
  qs.type = htons(DNS_TYPE_A);
  qs.class = htons(DNS_CLASS_IN);

  /* make message */
  *req_len = sizeof(s_dns_hs) + qname_len + sizeof(s_dns_qs);
  msg = calloc(1, *req_len);
  if (0 == msg)
    {
      fprintf(stderr, "! calloc: %s\n", strerror(errno));
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
  s_dns_rr  *rr                        =  0;
  uint16_t   rdlength                  =  0;
  size_t     qname_len                 =  0;
  uint8_t    qname[DNS_QNAME_MAX_LEN]  =  {0};

  rr = (s_dns_rr *) *offset;
  if (DNS_PTR_NAME == dns_ptr_type(rr->name))
    {
      parse_label(res, res + dns_ptr_offset(rr->name), qname, &qname_len);
    }
  rdlength = ntohs(rr->rdlength);
  *offset += sizeof(*rr);

  fprintf(stdout, " -> %s  %s  %s  %i  %u", qname,
          tr_dns_str(dns_type_str, rr->type, uint16_t, ntohs),
          tr_dns_str(dns_class_str, rr->class, uint16_t, ntohs),
          (int) ntohl(rr->ttl), rdlength);

  if (0 == rdlength)
    {
      fprintf(stdout, "\n");
      return 0;
    }

  fprintf(stdout, "  ");
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
      fprintf(stdout, "%s", (const char *) qname);
      break;
    case DNS_TYPE_A:
      fprintf(stdout, "%u.%u.%u.%u", (*offset)[0], (*offset)[1], (*offset)[2],
              (*offset)[3]);
      break;
    default:
      break;
    }
  fprintf(stdout, "\n");

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
  fprintf(stdout, "# header section:\n");

  fprintf(stdout, " -> ID  %u  <- %u\n", ntohs(hs->id), id);

  fprintf(stdout, " -> QR  %u  %s\n", hs->flags.qr,
          tr_dns_str(dns_qr_str, hs->flags.qr, uint16_t, (uint16_t)));

  fprintf(stdout, " -> AA  %u  %s\n", hs->flags.aa,
          tr_dns_str(dns_aa_str, hs->flags.aa, uint16_t, (uint16_t)));

  fprintf(stdout, " -> TC  %u  %s\n", hs->flags.tc,
          tr_dns_str(dns_tc_str, hs->flags.tc, uint16_t, (uint16_t)));

  fprintf(stdout, " -> OPCODE  %u  %s\n", hs->flags.opcode,
          tr_dns_str(dns_opcode_str, hs->flags.opcode, uint16_t, (uint16_t)));

  fprintf(stdout, " -> RCODE  %u  %s\n", hs->flags.rcode,
          tr_dns_str(dns_rcode_str, hs->flags.rcode, uint16_t, (uint16_t)));

  n = (ssize_t) ntohs(hs->qdcount);
  offset = res + sizeof(*hs);
  fprintf(stdout, "# question section: %zu\n", (size_t) n);
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

      fprintf(stdout, " -> %s  %s  %s\n", qname,
              tr_dns_str(dns_type_str, qs->type, uint16_t, ntohs),
              tr_dns_str(dns_class_str, qs->class, uint16_t, ntohs));

      offset += sizeof(*qs);
    }

  n = (ssize_t) ntohs(hs->ancount);
  fprintf(stdout, "# answer section: %zu\n", (size_t) n);
  while (n-- > 0)
    {
      if (0 == parse_rr(res, &offset))
        {
          continue;
        }
    }

  n = (ssize_t) ntohs(hs->nscount);
  fprintf(stdout, "# authority section: %zu\n", (size_t) n);
  while (n-- > 0)
    {
      if (0 == parse_rr(res, &offset))
        {
          continue;
        }
    }

  n = (ssize_t) ntohs(hs->arcount);
  fprintf(stdout, "# additional section: %zu\n", (size_t) n);
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
      fprintf(stderr, "! fopen: %s\n", strerror(errno));
      return;
    }

  len = fwrite(b, 1, n, f);
  if (ferror(f))
    {
      fprintf(stderr, "! fwrite: %s\n", strerror(errno));
      clearerr(f);
      goto clean_exit;
    }
  if (len < n)
    {
      fprintf(stderr, "! fwrite: %zu/%zu\n", len, n);
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
      fprintf(stderr, "! fopen: %s\n", strerror(errno));
      return;
    }

  n = fread(b, 1, DNS_UDP_MAX_LEN, f);
  if (ferror(f))
    {
      fprintf(stderr, "! fread: %s\n", strerror(errno));
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
  fprintf(stderr, "!%s: %d\n", __FUNCTION__, sig);
  exit(EXIT_FAILURE);
}
#endif  /* NDEBUG */


int
main(int argc, char* argv[])
{
  int  ch;

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
      fprintf(stderr, "! signal: %s\n", strerror(errno));
      goto clean_exit;
    }
#endif  /* NDEBUG */

  while (-1 != (ch = getopt_long(argc, argv,
                                 "hs:p:q:r:t:oi:v:",
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
        case 'v':
          opt_verbose = atoi(optarg);
          break;
        default:
          usage(argv[0]);
          goto clean_exit;
        }
    }

  opt_verbose %= 3;

  if (opt_in)
    {
      printf("# command line options:\n"
             " -> --in=%s -verbose=%d\n",
             opt_file,
             opt_verbose);
      in(opt_file);
    }
  else
    {
      printf("# command line options:\n"
             " -> --query=%s --server=%s --port=%d"
             " --retry=%d --timeout=%d --out=%s -verbose=%d\n",
             opt_query,
             opt_server,
             opt_port,
             (int) opt_retry,
             (int) opt_timeout.tv_sec,
             opt_out ? opt_file : "",
             opt_verbose);
      query();
    }

 clean_exit:
  return 0;
}


/* eof */
