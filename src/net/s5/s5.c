#include "_net_.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>


/*
 * References:
 * 1. https://datatracker.ietf.org/doc/html/rfc1928
 * 2. https://datatracker.ietf.org/doc/html/rfc1929
 *
 */

#define S5_VER  0x5

#define BUF_MAX   512
#define ADDR_MAX  256
#define PATH_MAX  256
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


enum s5_seq_e
  {
    S5_SEQ_SELECT   =  0x00,
    S5_SEQ_CONNECT  =  0x01,
    S5_SEQ_RELAY    =  0x02

  };



#define log(...)                                \
  if (opt_quiet < 1)                            \
    {                                           \
      fprintf(stdout, __VA_ARGS__);             \
    }


#define log_err(...)                            \
  if (opt_quiet <= 1)                           \
    {                                           \
      fprintf(stderr, __VA_ARGS__);             \
    }


#if (NDEBUG)
#define log_buf(name, buf, n)                   \
  {                                             \
    _unused_(n);                                \
  }
#else

#define log_buf(name, buf, n)                   \
  if (opt_output && (opt_quiet < 1))            \
    {                                           \
      s5_output((name), (buf), (n));            \
    }
#endif


typedef struct s5_addr_s
{
  uint16_t    port;
  in_addr_t   r;

} s5_addr_t;


typedef union s5_socks_addr_u
{
  struct
  {
    uint32_t addr4;
    uint16_t port;
  } ip4;

  struct
  {
    uint32_t addr6[4];
    uint16_t port;
  } ip6;

  struct
  {
    uint8_t  addr_len;
    uint8_t  addr_buf[ADDR_MAX - sizeof(uint8_t)];
    uint16_t port;
  } domain;

} s5_socks_addr_t;


typedef struct s5_sel_req_s
{
  uint8_t  ver;
  uint8_t  n_methods;
  uint8_t  methods;

} s5_sel_req_t;



typedef struct s5_sel_res_s
{
  uint8_t ver;
  uint8_t method;

} s5_sel_res_t;


#pragma pack(push, 1)
typedef struct s5_cmd_req_s
{
  uint8_t ver;
  uint8_t cmd;
  uint8_t rsv;
  uint8_t atyp;
  s5_socks_addr_t dst_addr;

} s5_cmd_req_t;
#pragma pack(pop)


#pragma pack(push, 1)
typedef struct s5_cmd_res_s
{
  uint8_t ver;
  uint8_t rep;
  uint8_t rsv;
  uint8_t atyp;
  uint32_t bnd_addr;
  uint16_t bnd_port;

} s5_cmd_res_t;
#pragma pack(pop)

typedef void (*on_signal)(int);

static void on_signal_chld(int signo);
static void on_signal_from_parent(int signo);
static void on_signal_from_child(int signo);


static int s5_connect(const struct sockaddr_in *addr);
static int s5_listen(int *sfd, const struct sockaddr_in *laddr);

static int s5_socks(const struct sockaddr_in *laddr,
                    const struct sockaddr_in *paddr);

static void s5_socks_req(int cfd, const struct sockaddr_in *caddr,
                         const struct sockaddr_in *paddr);

static int s5_socks_sel_reply(int cfd, const s5_sel_req_t *req);
static int s5_socks_cmd_reply(int cfd, const s5_cmd_req_t *req,
                              struct sockaddr_in *addr);

static int s5_proxy(const struct sockaddr_in *laddr,
                    const struct sockaddr_in *paddr);

static void s5_proxy_forward(int cfd, const struct sockaddr_in *addr);

static void s5_proxy_backward(int cfd, int sfd);

static int s5_socks_addr_get(struct sockaddr_in *addr, const s5_cmd_req_t * cmd);
static void s5_fd_set(int fd, fd_set *fds, int *nfds);

#if !(NDEBUG)
static void s5_output(const char *name, const uint8_t *buf, size_t n);
#endif


static struct option longopts[]  =
  {
    { "help",         no_argument,          0,              'h' },
    { "listen",       optional_argument,    0,              'L' },
    { "listen-port",  no_argument,          0,              'K' },
    { "proxy",        optional_argument,    0,              'P' },
    { "proxy-port",   optional_argument,    0,              'p' },
    { "proxy-only",   no_argument,          0,              'O' },
    { "timeout",      optional_argument,    0,              'T' },
    { "quiet",        optional_argument,    0,              'Q' },
    { "output",       no_argument,          0,              'o' },
    { 0,              0,                    0,               0  }
  };


static char            opt_listen[ADDR_MAX]  =  "127.0.0.1";
static uint16_t        opt_listen_port       =  9192;
static int             opt_listen_only       =  0;
static char            opt_proxy[ADDR_MAX]   =  "127.0.0.1";
static uint16_t        opt_proxy_port        =  9394;
static int             opt_proxy_only        =  0;
static int             opt_quiet             =  0;
static struct timeval  opt_timeout           =
  {
    .tv_sec = 15,
    .tv_usec = 0
  };
static int             opt_output            =  0;


static struct sockaddr_in opt_listen_addr;
static struct sockaddr_in opt_proxy_addr;


static void
usage(const char *p)
{
  printf("Usage %s [options ...]\n", p);
  printf("  -h, --help         this help text\n");
  printf("  -L, --listen       listen address, default is %s\n", opt_listen);
  printf("  -l, --listen-port  listen port, default is %d\n",
         opt_listen_port);
  printf("  -K, --listen-only  listen only, default is %d\n",
         opt_listen_only);
  printf("  -P, --proxy        serving as proxy\n");
  printf("  -p, --proxy-port   proxy port, default is %d\n",
         opt_proxy_port);
  printf("  -O, --proxy-only   proxy only, default is %d\n", opt_proxy_only);
  printf("  -T, --timeout      timeout in seconds, default is %d\n",
         (int) opt_timeout.tv_sec);
  printf("  -Q, --quiet        quiet mode:0,1,2, default is %d\n",
         opt_quiet);
}


void
on_signal_chld(int signo)
{
  int    stat;
  pid_t  pid;

  if (SIGCHLD == signo)
    {
      log("!on_signal_chld[%d]\n", getpid());

      pid = wait(&stat);
      if (-1 == pid)
        {
          log_err("!signal: %s\n", strerror(errno));
        }
    }
}

static void
on_signal_from_parent(int signo)
{
  if (SIGUSR1 == signo)
    {
      log("!on_signal_from_parent[%d]\n", getpid());
      exit(0);
    }
}

static void
on_signal_from_child(int signo)
{
  if (SIGUSR2 == signo)
    {
      log("!on_signal_from_child(%d)\n", signo);
    }
}


static int
s5_connect(const struct sockaddr_in *addr)
{
  int             rc;
  int             fd;
  int             nfds;
  fd_set          fds;
  struct timeval  timeout;

  rc = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
  if (-1 == rc)
    {
      log_sockerr(rc, "!socket: %s\n");
      return -1;
    }
  fd = rc;

  for (;;)
    {
      memset(&timeout, 0, sizeof(timeout));
      FD_ZERO(&fds);
      s5_fd_set(fd, &fds, &nfds);

      rc = select(nfds, &fds, NULL, NULL, &timeout);
      if (-1 == rc)
        {
          log_err("!select: %s\n", strerror(errno));
          goto clean_exit;
        }

      if (FD_ISSET(fd, &fds))
        {
          rc = connect(fd, (const struct sockaddr *) addr, sizeof(*addr));
          if (-1 == rc)
            {
              log_sockerr(rc, "!connect: %s\n");
              goto clean_exit;
            }
          return fd;
        }
    }

 clean_exit:
  close(fd);
  return -1;

}


static int
s5_listen(int *sfd, const struct sockaddr_in *laddr)
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
      log_sockerr(rc, "!setsocketopt: %s\n");
      goto clean_exit;
    }


  rc = bind(*sfd, (const struct sockaddr *) laddr, sizeof(*laddr));
	if (rc)
    {
      log_sockerr(rc, "!bind: %s\n");
      goto close_exit;
    }

  rc = listen(*sfd, BACKLOG);
	if (rc)
    {
      log_sockerr(rc, "!listen: %s\n");
      goto close_exit;
    }

  goto clean_exit;

 close_exit:
  close(*sfd);

 clean_exit:

  return rc;
}



static void
s5_socks_req(int cfd, const struct sockaddr_in *caddr,
             const struct sockaddr_in *paddr)
{
  int                 rc    =  0;
  int                 n, e;
  int                 nfds  =  0;
  int                 seq   =  S5_SEQ_SELECT;
	uint8_t             buf[BUF_MAX];
  pid_t               pid;
  fd_set              rfds, wfds;
  struct timeval      timeout;
  struct sockaddr_in  addr;

  pid = getpid();

  log("#s5_socks_req[pid:%d]: %s:%d to %s:%d\n",
      pid,
      inet_ntoa(caddr->sin_addr),
      ntohs(caddr->sin_port),
      inet_ntoa(paddr->sin_addr),
      ntohs(paddr->sin_port));


  for (;;)
    {
      memcpy(&timeout, &opt_timeout, sizeof(timeout));
      FD_ZERO(&rfds);
      FD_ZERO(&wfds);
      s5_fd_set(cfd, &rfds, &nfds);

      rc = select(nfds, &rfds, NULL, NULL, &timeout);
      if (-1 == rc)
        {
          e = errno;
          log_err("!select: %s\n", strerror(e));
          if (e == EINTR)
            {
              continue;
            }
          else
            {
              goto clean_exit;
            }
        }

      if (0 == rc)
        {
          goto clean_exit;
        }

      if (FD_ISSET(cfd, &rfds))
        {
          memset(buf, 0, sizeof(buf));
          rc = read(cfd, buf, sizeof(buf));
          if (-1 == rc)
            {
              log_err("!read: %s\n", strerror(errno));
              goto clean_exit;
            }

          if (0 == rc)
            {
              goto clean_exit;
            }

          n = rc;

          log_buf("rr", buf, n);

          FD_SET(cfd, &wfds);
        }

      if (FD_ISSET(cfd, &wfds))
        {
          FD_CLR(cfd, &wfds);

          switch (seq)
            {
            case S5_SEQ_RELAY:
              log("# xxx, %s, %d\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
              s5_proxy_forward(cfd, &addr);
              break;

            case S5_SEQ_SELECT:
              s5_socks_sel_reply(cfd, (const s5_sel_req_t *) buf);
              seq = S5_SEQ_CONNECT;
              break;

            case S5_SEQ_CONNECT:
              s5_socks_cmd_reply(cfd, (const s5_cmd_req_t *) buf, &addr);
              seq = S5_SEQ_RELAY;
              break;

            default:
              goto clean_exit;
            }

        }

    }


 clean_exit:
  close(cfd);
  exit(rc);
}


static int
s5_socks_sel_reply(int cfd, const s5_sel_req_t *req)
{
  int           rc  =  0;
  s5_sel_res_t  res;

  if (req->ver != S5_VER)
    {
      log("!socks: version: %d not support\n", req->ver);
      rc = -1;
      goto clean_exit;
    }

  memset(&res, 0, sizeof(res));
  res.ver = S5_VER;
  res.method = 0;

  rc = write(cfd, &res, sizeof(res));
  if (-1 == rc)
    {
      log_err("!s5: %s\n", strerror(rc));
      goto clean_exit;
    }

  log_buf("sw", (const uint8_t *) &res, rc);

 clean_exit:
  return rc;
}

static int
s5_socks_cmd_reply(int cfd, const s5_cmd_req_t *req, struct sockaddr_in *addr)
{
  int           rc  =  0;
  uint32_t      ip4;
  s5_cmd_res_t  res;


  if (req->ver != S5_VER)
    {
      log_err("!socks: version: %d not support\n", req->ver);
      rc = -1;
      goto clean_exit;
    }

  switch (req->cmd)
    {
    case S5_CMD_CONNECT:

      memset(addr, 0, sizeof(in_addr_t));
      s5_socks_addr_get(addr, req);

      memset(&res, 0, sizeof(res));
      res.ver = S5_VER;
      res.rep = S5_REP_SUCCEEDED;
      res.atyp = S5_ATYP_IPv4;
      res.bnd_port = opt_proxy_addr.sin_port;
      ip4 = ntohl(opt_proxy_addr.sin_addr.s_addr);
      memcpy(&res.bnd_addr, &ip4, sizeof(ip4));

      rc = write(cfd, &res, sizeof(res));
      if (-1 == rc)
        {
          log_err("!write: %s\n", strerror(rc));
          goto clean_exit;
        }

      log_buf("cw", (const uint8_t *) &res, rc);
      break;

    default:
      rc = -1;
      break;
    }

 clean_exit:
  return rc;
}


static void
s5_proxy_forward(int cfd, const struct sockaddr_in *paddr)
{
  int             rc    =  0;
  int             sfd;
  int             n, e;
  int             nfds  =  0;
  char            buf[BUF_MAX];
  pid_t           pid   =  0;
  fd_set          rfds, wfds;
  struct timeval  timeout;

  log("!proxy[froward@%d]: to %s:%d\n",
      getpid(),
      inet_ntoa(paddr->sin_addr),
      ntohs(paddr->sin_port));

  log("!proxy[%d]: connecting ...\n", getpid());

  /* if (!opt_listen_only) */
  /*   { */
      sfd = s5_connect(paddr);
      if (-1 == sfd)
        {
          goto clean_exit;
        }

      log("!proxy[%d]: connected ...\n", getpid());

      pid = fork();
      if (-1 == pid)
        {
          log_err("!fork: %s\n", strerror(errno));
        }
      else if (0 == pid)
        {
          s5_proxy_backward(cfd, sfd);
        }

    /* } /\* !opt_listen_only *\/ */

  n = 0;
  FD_ZERO(&wfds);

  for (;;)
    {
      memcpy(&timeout, &opt_timeout, sizeof(timeout));

      FD_ZERO(&rfds);
      s5_fd_set(cfd, &rfds, &nfds);

      log("!select[%d]: selecting %d ...\n", getpid(), cfd);

      rc = select(nfds, &rfds, NULL, NULL, &timeout);
      if (-1 == rc)
        {
          e = errno;
          log_err("!select[%d]: %s\n", getpid(), strerror(e));
          goto clean_exit;
        }

      if (0 == rc)
        {
          goto clean_exit;
        }

      log("!select[%d]: selected %d\n", getpid(), cfd);

      if (FD_ISSET(cfd, &rfds))
        {
          memset(buf, 0, sizeof(buf));

          rc = read(cfd, buf, sizeof(buf));
          if (-1 == rc)
            {
              log_err("!read[%d]: %s\n", getpid(), strerror(errno));
              goto clean_exit;
            }

          if (0 == rc)
            {
              goto clean_exit;
            }

          if (opt_listen_only)
            {
              log("!read[%d]: %s\n", getpid(), buf);
            }

          n = rc;
          FD_SET(sfd, &wfds);
        }

      if (FD_ISSET(sfd, &wfds))
        {
          FD_CLR(sfd, &wfds);

          if (!opt_listen_only)
            {
              rc = write(sfd, buf, n);
              if (-1 == rc)
                {
                  log_err("!write[%d]: %s", getpid(), strerror(errno));
                  goto clean_exit;
                }

              if (n != rc)
                {
                  goto clean_exit;
                }
            }
        }

      n = 0;
    }

 clean_exit:
  if (pid > 0)
    {
      kill(pid, SIGUSR1);
    }
  close(sfd);
  close(cfd);
  exit(0);

}

static void
s5_proxy_backward(int cfd, int sfd)
{
  int             rc  =  0;
  int             n, e;
  int             nfds;
  char            buf[BUF_MAX];
  fd_set          rfds, wfds;
  struct timeval  timeout;

  log("!proxy [backward:%d]: \n", getpid());

  n = 0;
  FD_ZERO(&wfds);

  for (;;)
    {
      memcpy(&timeout, &opt_timeout, sizeof(timeout));

      FD_ZERO(&rfds);
      s5_fd_set(sfd, &rfds, &nfds);

      rc = select(nfds, &rfds, NULL, NULL, &timeout);
      if (-1 == rc)
        {
          e = errno;
          log_err("!select[%d]: %s\n", getpid(), strerror(e));
          goto clean_exit;
        }

      if (0 == rc)
        {
          goto clean_exit;
        }

      log("!proxy[backward:%d]: [selected:%d] [r:%d|%d], [w:%d]\n",
          getpid(), rc, sfd, FD_ISSET(sfd, &rfds), cfd);

      if (FD_ISSET(sfd, &rfds))
        {
          memset(buf, 0, sizeof(buf));

          rc = read(sfd, buf, sizeof(buf));
          if (-1 == rc)
            {
              log_err("!read[%d]: %s\n", getpid(), strerror(errno));
              goto clean_exit;
            }

          if (0 == rc)
            {
              goto clean_exit;
            }

          n = rc;

          FD_SET(cfd, &wfds);
        }

      if (FD_ISSET(cfd, &wfds))
        {
          FD_CLR(cfd, &wfds);

          rc = write(cfd, buf, n);
          if (-1 == rc)
            {
              log_err("!write[%d]: %s", getpid(), strerror(errno));
              goto clean_exit;
            }

          if (rc != n)
            {
              goto clean_exit;
            }
        }

    }

 clean_exit:
  exit(0);
}


static int
s5_socks_addr_get(struct sockaddr_in *addr, const s5_cmd_req_t * cmd)
{
  switch (cmd->atyp)
    {
    case S5_ATYP_IPv4:
      addr->sin_addr.s_addr = ntohl(cmd->dst_addr.ip4.addr4);
      addr->sin_port = cmd->dst_addr.ip4.port;
      return 0;

    default:
      return 1;
    }
}

static void
s5_fd_set(int fd, fd_set *fds, int *nfds)
{
  FD_SET(fd, fds);
  if (*nfds <= fd)
    {
      *nfds = fd + 1;
    }
}

#if !(NDEBUG)
static void
s5_output(const char *name, const uint8_t *buf, size_t nbuf)
{
  int          rc;
  FILE        *f   =  0;
  char         path[PATH_MAX];
  size_t       len;
  static int   sn  =  0;

  if (0 == getcwd(path, sizeof(path)))
    {
      perror(NULL);
      return;
    }

  len = strlen(path);
  rc = sprintf(path + len, "/%d-%d-%s.out", getpid(), sn++, name);
  if (rc <= 0)
    {
      goto clean_exit;
    }

  f = fopen(path, "wb");
  if (!f)
    {
      log_err("!s5_output: %s\n", strerror(errno));
      return;
    }

  fwrite(buf, 1, nbuf, f);

  log("#s5_output: %s\n", path);

  if (ferror(f))
    {
      clearerr(f);
      goto clean_exit;
    }

 clean_exit:
  fclose(f);
}
#endif  /* NDEBUG: s5_output */

static int
s5_proxy(const struct sockaddr_in *laddr, const struct sockaddr_in *paddr)
{
  int                 rc  =  0;
  int                 sfd, cfd;
  pid_t               pid;
  socklen_t           slen;
  struct sockaddr_in  caddr;

  sfd = 0;

  rc = s5_listen(&sfd, laddr);
  if (-1 == rc)
    {
      goto clean_exit;
    }

  for (;;)
    {
      slen = sizeof(caddr);
      cfd = accept(sfd, (struct sockaddr*) &caddr, &slen);
      if (-1 == cfd)
        {
          log_sockerr(rc, "!accept: %s\n");
          continue;
        }

      pid = fork();
      if (-1 == pid)
        {
          log_err("!fork: %s\n", strerror(errno));
        }
      else if (0 == pid)
        {
          s5_proxy_forward(cfd, paddr);
        }
      else
        {
          /* void */
        }

    }

  close(sfd);

 clean_exit:
  return rc;
}

static int
s5_socks(const struct sockaddr_in *laddr, const struct sockaddr_in *paddr)
{
  int        rc  =  0;
  int        sfd, cfd;
  pid_t      pid;
  socklen_t  slen;

  struct sockaddr_in  caddr;

  rc = s5_listen(&sfd, laddr);
  if (-1 == rc)
    {
      goto clean_exit;
    }

  for (;;)
    {
      slen = sizeof(caddr);
      cfd = accept(sfd, (struct sockaddr*) &caddr, &slen);
      if (-1 == cfd)
        {
          log_sockerr(rc, "!accept: %s\n");
          goto close_exit;
        }

      pid = fork();
      if (-1 == pid)
        {
          log_err("!fork: %s\n", strerror(errno));
        }

      if (0 == pid)
        {
          s5_socks_req(cfd, (const struct sockaddr_in *) &caddr, paddr);
        }

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

  while (-1 != (ch = getopt_long(argc, argv,
                                 "hl:L:Kp:P:OT:Q:o",
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
        case 'K':
          opt_listen_only = 1;
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
          if (optarg)
            {
              opt_quiet = atoi(optarg);
            }
          break;
        case 'o':
          opt_output = 1;
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
  log("# command line options @%d:\n"
      " -> --listen=%s --listen-port=%d --listen-only=%d\n"
      " -> --proxy=%s --proxy-port=%d --proxy-only=%d\n"
      " -> --timeout=%d --quiet=%d\n"
      " -> --output=%d\n",
      getpid(),
      opt_listen,
      opt_listen_port,
      opt_listen_only,
      opt_proxy,
      opt_proxy_port,
      opt_proxy_only,
      (int) opt_timeout.tv_sec,
      opt_quiet,
      opt_output);


#endif  /* NDEBUG */

  memset(&opt_listen_addr, 0, sizeof(opt_listen_addr));
  memset(&opt_proxy_addr, 0, sizeof(opt_proxy_addr));

  opt_listen_addr.sin_family = AF_INET;
  opt_listen_addr.sin_port = htons(opt_listen_port);
  opt_listen_addr.sin_addr.s_addr = inet_addr(opt_listen);

  opt_proxy_addr.sin_family = AF_INET;
  opt_proxy_addr.sin_port = htons(opt_proxy_port);
  opt_proxy_addr.sin_addr.s_addr = inet_addr(opt_proxy);


  signal(SIGCHLD, on_signal_chld);
  signal(SIGUSR1, on_signal_from_parent);
  signal(SIGUSR2, on_signal_from_child);


  if (opt_proxy_only)
    {
      rc = s5_proxy(&opt_listen_addr, &opt_proxy_addr);
    }
  else
    {
      opt_proxy_only = !opt_proxy_only;
      rc = s5_socks(&opt_listen_addr, &opt_proxy_addr);
    }

  _unused_(s5_socks_addr_get);

 clean_exit:
  return rc;
}


/* eof */
