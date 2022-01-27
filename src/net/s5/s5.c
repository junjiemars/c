#include "_net_.h"
#include <getopt.h>
#include <string.h>
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
  uint8_t bnd_buf[ADDR_MAX];

} s5_cmd_res_t;


#if !(NDEBUG)
typedef void (*on_signal)(int);
static void on_signal_segv(int sig);
#endif  /* NDEBUG */


static void s5_cmd_process(int cfd);
static int s5_listen(void);

static struct option longopts[]  =
  {
    { "help",    no_argument,          0,              'h' },
    { "port",    optional_argument,    0,              'p' },
    { "timeout", optional_argument,    0,              'T' },
    { "quiet",   no_argument,          0,              'Q' },
    { 0,         0,                    0,               0  }
  };


static uint16_t        opt_port     =  9192;
static int             opt_quiet    =  0;
static struct timeval  opt_timeout  =  { .tv_sec = 15, 0 };


static void
usage(const char *p)
{
  printf("Usage %s [options ...]\n", p);
  printf("  -h, --help     this help text\n");
  printf("  -p, --port     listen port, default is %d\n", opt_port);
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
s5_cmd_process(int cfd)
{
  int               rc          =  0;
	char              buf[BUF_MAX];
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
              log(stderr, "!s5: unsupport socks version: %d\n", req_cmd->ver);
              goto clean_exit;
            }

          memset(&res_select, 0, sizeof(res_select));
          res_select.ver = S5_VER;
          res_select.method = 0;

          rc = write(cfd, &res_select, sizeof(res_select));
          if (-1 == rc)
            {
              log(stderr, "!s5: YYY %s\n", strerror(rc));
              goto clean_exit;
            }
        }
      else if (n > 0)
        {
          req_cmd = (s5_cmd_req_t *) &buf;
          if (req_cmd->ver != S5_VER)
            {
              log(stderr, "!s5: unsupport socks version: %d\n", req_cmd->ver);
              goto clean_exit;
            }

          if (req_cmd->cmd == S5_CMD_CONNECT)
            {
              memset(&res_cmd, 0, sizeof(res_cmd));
              res_cmd.ver = S5_VER;
              res_cmd.rep = S5_REP_SUCCEEDED;

              rc = write(cfd, &res_cmd, sizeof(res_cmd));
              if (-1 == rc)
                {
                  log(stderr, "!s5: XXX %s\n", strerror(rc));
                  goto clean_exit;
                }

            }
        }
    }

 clean_exit:
  close(cfd);
  /* _exit(rc); */
}


static int
s5_listen(void)
{
  int                 rc  =  0;
  int                 sfd, cfd;
  pid_t               pid;
  socklen_t           size;
  struct sockaddr_in  srv, clt;

#if (WINNT)
  WSADATA wsa;
  rc = WSAStartup(MAKEWORD(2, 2), &wsa);
  if (rc)
    {
      rc = errno;
      log(stderr, "! WSAStartup: %s\n", strerror(rc));
      goto clean_exit;
    }
#endif  /* WINNT */

  sfd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (-1 == sfd)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto clean_exit;
    }

  memset(&srv, 0, sizeof(srv));

	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = htonl(INADDR_ANY);
	srv.sin_port = htons(opt_port);

  rc = bind(sfd, (const struct sockaddr*) &srv, sizeof(srv));
	if (rc)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto close_exit;
    }

  rc = listen(sfd, 5);
	if (rc)
    {
      log_sockerr(rc, "!socket: %s\n");
      goto close_exit;
    }

  for (;;)
    {
      size = sizeof(clt);
      cfd = accept(sfd, (struct sockaddr*) &clt, &size);
      if (-1 == cfd)
        {
          log_sockerr(rc, "!socket: %s\n");
          goto close_exit;
        }

#if (!NDEBUG)
      pid = fork();
      if (-1 == pid)
        {
          log(stderr, "!s5: %s\n", strerror(errno));
        }

      if (0 == pid)
        {
          _unused_(pid);
          s5_cmd_process(cfd);
        }

#else
      _unused_(pid);
      s5_cmd_process(cfd);

#endif

    }


 close_exit:
  close(sfd);

 clean_exit:
#if (WINNT)
  WSACleanup();
#endif  /* WINNT */

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
                                 "hp:T:Q",
                                 longopts, 0)))
    {
      switch (ch)
        {
        case 'p':
          opt_port = (uint16_t) atoi(optarg);
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
      " -> --port=%d --timeout=%d --quiet=%d\n",
      opt_port,
      (int) opt_timeout.tv_sec,
      opt_quiet);
#endif  /* NDEBUG */

  /* !TODO: */
  rc = s5_listen();

 clean_exit:
  return rc;
}


/* eof */
