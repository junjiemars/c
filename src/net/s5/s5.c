#include "_net_.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>

#if !(NDEBUG)
#include <signal.h>
#endif  /* NDEBUG */


/*
 * References:
 * 1. https://datatracker.ietf.org/doc/html/rfc1928
 * 2. https://datatracker.ietf.org/doc/html/rfc1929
 *
 */

#define S5_VER  0x5

#define BUF_MAX   512
#define ADDR_MAX  256
#define BACKLOG   4


#define S5_CMD_MAP(XX)                          \
  XX(0x01, CONNECT)                             \
  XX(0x02, BIND)                                \
  XX(0x03, UDP)                                 \

enum s5_cmd
  {
#define XX(n, s) S5_CMD_##s = n,
    S5_CMD_MAP(XX)
#undef XX
  };


#define S5_ATYP_MAP(XX)                         \
  XX(0x01, IPv4)                                \
  XX(0x03, DOMAINNAME)                          \
  XX(0x04, IPv6)                                \

enum s5_atyp
  {
#define XX(n, s) S5_ATYP_##s = n,
    S5_ATYP_MAP(XX)
#undef XX
  };


#define S5_REP_MAP(XX)                          \
  XX(0x00, SUCCEEDED)                           \
  XX(0x01, SERVER_FAILURE)                      \
  XX(0x02, CONNECT_NOT_ALLOWED)                 \
  XX(0x03, NETWORK_UNREACHABLE)                 \
  XX(0x04, HOST_UNREACHABLE)                    \
  XX(0x05, CONNECT_REFUSED)                     \
  XX(0x06, TTL_EXPIRED)                         \
  XX(0x07, CMD_NOT_SUPPORTED)                   \
  XX(0x08, ATYP_NOT_SUPPORTED)                  \
  XX(0x09, UNASSIGNED)                          \

enum s5_rep
  {
#define XX(n, s) S5_REP_##s = n,
    S5_REP_MAP(XX)
#undef XX
  };



#define log(x, ...)                             \
  if (0 == opt_quiet)                           \
    {                                           \
      fprintf(x, __VA_ARGS__);                  \
    }



typedef struct s5_addr_s
{
  uint16_t    port;
  in_addr_t   r;

} s5_addr_t;


typedef union s5_socks_addr_u
{
  struct
  {
    uint32_t ip4;
  } ip4;

  struct
  {
    uint64_t ip6[2];
  } ip6;

  struct
  {
    uint8_t  addr_len;
    uint8_t  addr_buf[ADDR_MAX - sizeof(uint8_t)];
  } domain;

} s5_socks_addr_t;


typedef struct s5_select_req_s
{
  uint8_t  ver;
  uint8_t  n_methods;
  uint8_t  methods;

} s5_select_req_t;


typedef struct s5_select_res_s
{
  uint8_t ver;
  uint8_t method;

} s5_select_res_t;


typedef struct s5_cmd_req_s
{
  uint8_t ver;
  uint8_t cmd;
  uint8_t rsv;
  uint8_t atyp;
  s5_socks_addr_t dst_addr;

} s5_cmd_req_t;


typedef struct s5_cmd_res_s
{
  uint8_t ver;
  uint8_t rep;
  uint8_t rsv;
  uint8_t atyp;
  uint8_t bnd_addr_len;
  uint32_t bnd_addr;
  uint16_t bnd_port;

} s5_cmd_res_t;


typedef void (*on_signal)(int);


#if !(NDEBUG)
static void on_signal_segv(int sig);

#endif  /* NDEBUG */


static int s5_listen(int *sfd, struct sockaddr_in *laddr);
static int s5_socks(struct sockaddr_in *laddr, struct sockaddr_in *paddr);
static void s5_socks_cmd(int cfd, struct sockaddr_in *paddr);

static int s5_proxy(struct sockaddr_in *laddr, struct sockaddr_in *paddr);
static void s5_proxy_cmd(int cfd, struct sockaddr_in *addr);


static struct option longopts[]  =
  {
    { "help",         no_argument,          0,              'h' },
    { "listen-port",  optional_argument,    0,              'l' },
    { "proxy",        optional_argument,    0,              'P' },
    { "proxy-port",   optional_argument,    0,              'p' },
    { "proxy-only",   optional_argument,    0,              'O' },
    { "timeout",      optional_argument,    0,              'T' },
    { "quiet",        no_argument,          0,              'Q' },
    { 0,              0,                    0,               0  }
  };


static char            opt_listen[ADDR_MAX]  =  "127.0.0.1";
static uint16_t        opt_listen_port       =  9192;
static char            opt_proxy[ADDR_MAX]   =  "127.0.0.1";
static uint16_t        opt_proxy_port        =  9394;
static int             opt_proxy_only        =  0;
static int             opt_quiet             =  0;
static struct timeval  opt_timeout           =  { .tv_sec = 15, 0 };


static void
usage(const char *p)
{
  printf("Usage %s [options ...]\n", p);
  printf("  -h, --help         this help text\n");
  printf("  -L, --listen       listen address, default is %s\n", opt_listen);
  printf("  -l, --listen-port  listen port, default is %d\n",
         opt_listen_port);
  printf("  -P, --proxy        serving as proxy\n");
  printf("  -p, --proxy-port   proxy port, default is %d\n",
         opt_proxy_port);
  printf("  -O, --proxy-only   proxy only, default is %d\n", opt_proxy_only);
  printf("  -T, --timeout      timeout in seconds, default is %d\n",
         (int) opt_timeout.tv_sec);
  printf("  -Q, --quiet        quiet or silent mode\n");
}


#if !(NDEBUG)
void
on_signal_segv(int sig)
{
  log(stderr, "!%s: %d\n", __FUNCTION__, sig);
  exit(EXIT_FAILURE);
}
#endif  /* NDEBUG */



static int
s5_listen(int *sfd, struct sockaddr_in *laddr)
{
  int  rc  =  0;

  *sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (-1 == *sfd)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto clean_exit;
    }

  rc = setsockopt(*sfd, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
  if (-1 == rc)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto clean_exit;
    }


  rc = bind(*sfd, (const struct sockaddr *) laddr, sizeof(*laddr));
	if (rc)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto close_exit;
    }


  /* if (*port == 0) */
  /*   { */
  /*     slen = sizeof(gsn); */
  /*     rc = getsockname(*sfd, (struct sockaddr *) &gsn, &slen); */
  /*     if (-1 == rc) */
  /*       { */
  /*         log_sockerr(rc, "!socket: %s\n"); */
  /*       } */
  /*     *port = gsn.sin_port; */
  /*   } */


  rc = listen(*sfd, BACKLOG);
	if (rc)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto close_exit;
    }

  goto clean_exit;

 close_exit:
  close(*sfd);

 clean_exit:

  return rc;
}



static void
s5_socks_cmd(int cfd, struct sockaddr_in *paddr)
{
  int               rc          =  0;
  int               port        =  0;
	char              buf[BUF_MAX];
  pid_t             pid;
  ssize_t           n;
  s5_cmd_req_t     *req_cmd     =  0;
  s5_cmd_res_t      res_cmd;
  s5_select_req_t  *req_select  =  0;
  s5_select_res_t   res_select;

  _unused_(paddr);

  for (;;)
    {
      memset(buf, 0, sizeof(buf));
      n = read(cfd, buf, sizeof(buf));
      if (-1 == n)
        {
          log(stderr, "!read: %s\n", strerror(errno));
          goto clean_exit;
        }

      if ((size_t) n == sizeof(s5_select_req_t))
        {
          req_select = (s5_select_req_t *) &buf;
          if (req_select->ver != S5_VER)
            {
              log(stderr, "!socks: version: %d not support\n", req_cmd->ver);
              goto clean_exit;
            }

          memset(&res_select, 0, sizeof(res_select));
          res_select.ver = S5_VER;
          res_select.method = 0;

          rc = write(cfd, &res_select, sizeof(res_select));
          if (-1 == rc)
            {
              log(stderr, "!s5: %s\n", strerror(rc));
              goto clean_exit;
            }
        }
      else if (n > 0)
        {
          req_cmd = (s5_cmd_req_t *) &buf;
          if (req_cmd->ver != S5_VER)
            {
              log(stderr, "!socks: version: %d not support\n", req_cmd->ver);
              goto clean_exit;
            }

          switch (req_cmd->cmd)
            {
            case S5_CMD_CONNECT:

#if (!NDEBUG)
              _unused_(pid);

              /* s5_proxy(port); */

#else
              pid = fork();
              if (-1 == pid)
                {
                  log(stderr, "!fork: %s\n", strerror(errno));
                  goto clean_exit;
                }

              if (0 == pid)
                {
                  /* s5_proxy(port); */
                }

#endif

              memset(&res_cmd, 0, sizeof(res_cmd));
              res_cmd.ver = S5_VER;
              res_cmd.rep = S5_REP_SUCCEEDED;
              res_cmd.atyp = S5_ATYP_IPv4;
              res_cmd.bnd_addr = htonl(INADDR_ANY);
              res_cmd.bnd_addr_len = sizeof(res_cmd.bnd_addr);
              res_cmd.bnd_port = port;

              rc = write(cfd, &res_cmd, sizeof(res_cmd));
              if (-1 == rc)
                {
                  log(stderr, "!write: %s\n", strerror(rc));
                  goto clean_exit;
                }
              break;

            default:
              break;
            }
        }
    }


 clean_exit:
  close(cfd);
}


static void
s5_proxy_cmd(int cfd, struct sockaddr_in *addr)
{
  int                 rc  =  0;
  int                 sfd;
	char                b1[BUF_MAX], b2[BUF_MAX];
  ssize_t             r1, w1, r2, w2;

  sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (-1 == sfd)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto clean_exit;
    }

  rc = connect(sfd, (const struct sockaddr *) addr, sizeof(*addr));
  if (-1 == rc)
    {
      log_sockerr(rc, "!connect: %s\n");
      goto clean_exit;
    }

  do
    {
      r1 = read(cfd, b1, sizeof(b1));
      if (-1 == r1)
        {
          log(stderr, "!read: %s\n", strerror(errno));
          goto clean_exit;
        }

      w1 = write(sfd, b1, r1);
      if (-1 == w1)
        {
          log(stderr, "!write: %s\n", strerror(errno));
          goto clean_exit;
        }

            r2 = read(sfd, b2, sizeof(b2));
      if (-1 == r2)
        {
          log(stderr, "!read: %s\n", strerror(errno));
          goto clean_exit;
        }

      w2 = write(cfd, b2, r2);
      if (-1 == w2)
        {
          log(stderr, "!write: %s\n", strerror(errno));
          goto clean_exit;
        }

    } while (r1 > 0);

 clean_exit:
  close(sfd);
  close(cfd);
}


static int
s5_proxy(struct sockaddr_in *laddr, struct sockaddr_in *paddr)
{
  int                 rc  =  0;
  int                 sfd, cfd;
  pid_t               pid;
  socklen_t           slen;
  struct sockaddr_in  clt;

  sfd = 0;

  rc = s5_listen(&sfd, laddr);
  if (-1 == rc)
    {
      goto clean_exit;
    }

  for (;;)
    {
      slen = sizeof(clt);
      cfd = accept(sfd, (struct sockaddr*) &clt, &slen);
      if (-1 == cfd)
        {
          log_sockerr(rc, "!accept: %s\n");
          goto close_exit;
        }

#if (!NDEBUG)
      _unused_(pid);

      s5_proxy_cmd(cfd, paddr);

#else
      pid = fork();
      if (-1 == pid)
        {
          log(stderr, "!fork: %s\n", strerror(errno));
        }

      if (0 == pid)
        {
          s5_proxy_cmd(cfd, paddr);
        }

#endif

    }


 close_exit:
  close(sfd);

 clean_exit:
  return rc;
}

static int
s5_socks(struct sockaddr_in *laddr, struct sockaddr_in *paddr)
{
  int                 rc  =  0;
  int                 sfd, cfd;
  pid_t               pid;
  socklen_t           slen;
  struct sockaddr_in  clt;

  rc = s5_listen(&sfd, laddr);
  if (-1 == rc)
    {
      goto clean_exit;
    }

  for (;;)
    {
      slen = sizeof(clt);
      cfd = accept(sfd, (struct sockaddr*) &clt, &slen);
      if (-1 == cfd)
        {
          log_sockerr(rc, "!socket: %s\n");
          goto close_exit;
        }

#if (!NDEBUG)
      _unused_(pid);

      s5_socks_cmd(cfd, paddr);

#else
      pid = fork();
      if (-1 == pid)
        {
          log(stderr, "!s5: %s\n", strerror(errno));
        }

      if (0 == pid)
        {
          s5_socks_cmd(cfd, paddr);
        }

#endif

    }


 close_exit:
  close(sfd);

 clean_exit:
  return rc;
}


int
main(int argc, char* argv[])
{
  int                 ch;
  int                 rc  =  0;
  struct sockaddr_in  laddr, paddr;


#if !(NDEBUG)

  on_signal  on_segv;
  on_segv = signal(SIGSEGV, on_signal_segv);
  if (SIG_ERR == on_segv)
    {
      log(stderr, "!signal: %s\n", strerror(errno));
      rc = 1;
      goto clean_exit;
    }

#endif  /* NDEBUG */


  while (-1 != (ch = getopt_long(argc, argv,
                                 "hl:L:p:P:OT:Q",
                                 longopts, 0)))
    {
      switch (ch)
        {
        case 'l':
          opt_listen_port = (uint16_t) atoi(optarg);
          break;
        case 'L':
          if (optarg)
            {
              strcpy(opt_listen, optarg);
            }
          break;
        case 'p':
          opt_proxy_port = atoi(optarg);
          break;
        case 'P':
          if (optarg)
            {
              strcpy(opt_proxy, optarg);
            }
          break;
        case 'O':
          opt_proxy_only = 1;
          break;
        case 'T':
          opt_timeout.tv_sec = atoi(optarg);
          break;
        case 'Q':
          opt_quiet = '\n';
          break;
        case 'h':
          usage(argv[0]);
          goto clean_exit;
        default:
          rc = 1;
          break;
        }
    }


#if !(NDEBUG)
  log(stdout, "# command line options:\n"
      " -> --listen=%s --listen-port=%d --proxy=%s --proxy-port=%d, "
      "--timeout=%d --quiet=%d\n",
      opt_listen,
      opt_listen_port,
      opt_proxy,
      opt_proxy_port,
      (int) opt_timeout.tv_sec,
      opt_quiet);

#endif  /* NDEBUG */

  memset(&laddr, 0, sizeof(laddr));
  memset(&paddr, 0, sizeof(paddr));

  laddr.sin_family = AF_INET;
  laddr.sin_port = htons(opt_listen_port);
  laddr.sin_addr.s_addr = inet_addr(opt_listen);

  paddr.sin_family = AF_INET;
  paddr.sin_port = htons(opt_proxy_port);
  paddr.sin_addr.s_addr = inet_addr(opt_proxy);

  if (opt_proxy_only)
    {
      rc = s5_proxy(&laddr, &paddr);
    }
  else
    {
      rc = s5_socks(&laddr, &paddr);
    }


 clean_exit:
  return rc;
}


/* eof */
