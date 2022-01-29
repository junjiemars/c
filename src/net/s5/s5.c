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
  uint8_t dst_addr_len;
  uint8_t dst_buf[ADDR_MAX];

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


#if !(NDEBUG)
typedef void (*on_signal)(int);
static void on_signal_segv(int sig);
#endif  /* NDEBUG */


static int s5_listen(int *sfd, int *port);
static int s5_socks(int port);
static void s5_socks_cmd(int cfd);
static int s5_proxy(int port);

static struct option longopts[]  =
  {
    { "help",    no_argument,          0,              'h' },
    { "port",    optional_argument,    0,              'p' },
    { "proxy",   optional_argument,    0,              'P' },
    { "timeout", optional_argument,    0,              'T' },
    { "quiet",   no_argument,          0,              'Q' },
    { 0,         0,                    0,               0  }
  };


static uint16_t        opt_port     =  9192;
static int             opt_proxy    =  0;
static int             opt_quiet    =  0;
static struct timeval  opt_timeout  =  { .tv_sec = 15, 0 };


static void
usage(const char *p)
{
  printf("Usage %s [options ...]\n", p);
  printf("  -h, --help     this help text\n");
  printf("  -p, --port     listen port, default is %d\n", opt_port);
  printf("  -P, --proxy    serving as proxy\n");
  printf("  -T, --timeout  timeout in seconds, default is %d\n",
         (int) opt_timeout.tv_sec);
  printf("  -Q, --quiet    quiet or silent mode\n");
}


#if !(NDEBUG)
void
on_signal_segv(int sig)
{
  log(stderr, "!%s: %d\n", __FUNCTION__, sig);
  exit(EXIT_FAILURE);
}
#endif  /* NDEBUG */

static void
s5_socks_cmd(int cfd)
{
  int               rc          =  0;
  int               sfd         =  0;
  int               port        =  0;
	char              buf[BUF_MAX];
  pid_t             pid;
  ssize_t           n;
  s5_cmd_req_t     *req_cmd     =  0;
  s5_cmd_res_t      res_cmd;
  s5_select_req_t  *req_select  =  0;
  s5_select_res_t   res_select;

  log(stdout, "#s5: pid=%d\n", getpid());

  for (;;)
    {
      memset(buf, 0, sizeof(buf));
      n = read(cfd, buf, sizeof(buf));
      if (-1 == n)
        {
          log(stderr, "!s5: %s\n", strerror(errno));
          goto clean_exit;
        }

      if ((size_t) n == sizeof(s5_select_req_t))
        {
          req_select = (s5_select_req_t *) &buf;
          if (req_select->ver != S5_VER)
            {
              log(stderr, "!s5: socks version: %d not support\n", req_cmd->ver);
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
              log(stderr, "!s5: socks version: %d not support\n", req_cmd->ver);
              goto clean_exit;
            }

          switch (req_cmd->cmd)
            {
            case S5_CMD_CONNECT:
              log(stdout, "#s5: receive connect command\n");

              s5_listen(&sfd, &port);

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
                  log(stderr, "!s5: %s\n", strerror(rc));
                  goto clean_exit;
                }

              pid = fork();
              if (-1 == pid)
                {
                  log(stderr, "!s5: fork failed: %s\n", strerror(errno));
                  goto clean_exit;
                }

              if (0 == pid)
                {
                  s5_proxy(port);
                }
              goto clean_exit;
              break;

            default:
              break;
            }
        }
    }


 clean_exit:
  close(cfd);
}

static int
s5_listen(int *sfd, int *port)
{
  int                 rc  =  0;
  socklen_t           gsn_size;
  struct sockaddr_in  srv;
  struct sockaddr_in  gsn;

  *sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (-1 == *sfd)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto clean_exit;
    }

  memset(&srv, 0, sizeof(srv));

	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = htonl(INADDR_ANY);
	srv.sin_port = htons(*port);

  rc = bind(*sfd, (const struct sockaddr *) &srv, sizeof(srv));
	if (rc)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto close_exit;
    }
  if (*port == 0)
    {
      gsn_size = sizeof(gsn);
      rc = getsockname(*sfd, (struct sockaddr *) &gsn, &gsn_size);
      if (-1 == rc)
        {
          log_sockerr(rc, "!socket: %s\n");
        }
      *port = gsn.sin_port;
    }

  rc = listen(*sfd, 5);
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


static int
s5_proxy(int port)
{
  int                 rc  =  0;
  int                 sfd, cfd;
  pid_t               pid;
  socklen_t           slen;
  struct sockaddr_in  clt;

  rc = s5_listen(&sfd, &port);
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

      s5_socks_cmd(cfd);

#else
      pid = fork();
      if (-1 == pid)
        {
          log(stderr, "!s5: %s\n", strerror(errno));
        }

      if (0 == pid)
        {
          _unused_(pid);
          s5_socks_cmd(cfd);
        }

#endif

    }


 close_exit:
  close(sfd);

 clean_exit:
  return rc;
}

static int
s5_socks(int port)
{
  int                 rc  =  0;
  int                 sfd, cfd;
  pid_t               pid;
  socklen_t           slen;
  struct sockaddr_in  clt;

  rc = s5_listen(&sfd, &port);
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

      s5_socks_cmd(cfd);

#else
      pid = fork();
      if (-1 == pid)
        {
          log(stderr, "!s5: %s\n", strerror(errno));
        }

      if (0 == pid)
        {
          _unused_(pid);
          s5_socks_cmd(cfd);
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
  int  ch;
  int  rc  =  0;

#if !(NDEBUG)
  on_signal  on_segv;
  on_segv = signal(SIGSEGV, on_signal_segv);
  if (SIG_ERR == on_segv)
    {
      log(stderr, "! signal: %s\n", strerror(errno));
      rc = 1;
      goto clean_exit;
    }
#endif  /* NDEBUG */

  while (-1 != (ch = getopt_long(argc, argv,
                                 "hp:PT:Q",
                                 longopts, 0)))
    {
      switch (ch)
        {
        case 'p':
          opt_port = (uint16_t) atoi(optarg);
          break;
        case 'P':
          opt_proxy = 1;
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
      " -> --port=%d --proxy=%d --timeout=%d --quiet=%d\n",
      opt_port,
      opt_proxy,
      (int) opt_timeout.tv_sec,
      opt_quiet);
#endif  /* NDEBUG */


  if (opt_proxy)
    {
      s5_proxy(opt_port);
    }
  else
    {
      rc = s5_socks(opt_port);
    }

 clean_exit:
  return rc;
}


/* eof */
