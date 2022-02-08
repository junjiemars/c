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
    uint32_t ip6[4];
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

static void on_signal_chld(int signo);
static void on_signal_from_parent(int signo);
static void on_signal_from_child(int signo);


static int s5_connect(const struct sockaddr_in *addr);
static int s5_listen(int *sfd, const struct sockaddr_in *laddr);

static int s5_socks(const struct sockaddr_in *laddr,
                    const struct sockaddr_in *paddr);

static void s5_socks_cmd(int cfd, const struct sockaddr_in *paddr);

static void s5_socks_cmd_reply(int cfd, const s5_cmd_req_t *req,
                               const char *buf, ssize_t nbuf);

static int s5_proxy(const struct sockaddr_in *laddr,
                    const struct sockaddr_in *paddr);

static void s5_proxy_forward(int cfd, const struct sockaddr_in *caddr,
                             const struct sockaddr_in *addr);

static void s5_proxy_backward(int cfd, int sfd);


static void s5_fd_set(int fd, fd_set *fds, int *nfds);
static void s5_output(const char *buf, size_t nbuf);


static struct option longopts[]  =
  {
    { "help",         no_argument,          0,              'h' },
    { "listen",       optional_argument,    0,              'L' },
    { "listen-port",  no_argument,          0,              'K' },
    { "proxy",        optional_argument,    0,              'P' },
    { "proxy-port",   optional_argument,    0,              'p' },
    { "proxy-only",   no_argument,          0,              'O' },
    { "timeout",      optional_argument,    0,              'T' },
    { "quiet",        no_argument,          0,              'Q' },
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
  printf("  -Q, --quiet        quiet or silent mode\n");
}


void
on_signal_chld(int signo)
{
  int    stat;
  pid_t  pid;

  if (SIGCHLD == signo)
    {
      log(stdout, "!on_signal_chld[%d]\n", getpid());

      pid = wait(&stat);
      if (-1 == pid)
        {
          log(stderr, "!signal: %s\n", strerror(errno));
        }
    }
}

static void
on_signal_from_parent(int signo)
{
  if (SIGUSR1 == signo)
    {
      log(stdout, "!on_signal_from_parent[%d]\n", getpid());
      exit(0);
    }
}

static void
on_signal_from_child(int signo)
{
  if (SIGUSR2 == signo)
    {
      log(stdout, "!on_signal_from_child(%d)\n", signo);
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
          log(stderr, "!select: %s\n", strerror(errno));
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
s5_socks_cmd(int cfd, const struct sockaddr_in *paddr)
{
  int               rc          =  0;
  int               e;
  int               port        =  0;
  int               nfds        =  0;
	char              buf[BUF_MAX];
  pid_t             pid;
  ssize_t           n;
  fd_set            rfds, wfds;
  s5_cmd_req_t     *req_cmd     =  0;
  s5_cmd_res_t      res_cmd;
  struct timeval    timeout;
  s5_select_req_t  *req_select  =  0;
  s5_select_res_t   res_select;

  log(stdout, "!socks[cmd@%d]: to %s:%d\n",
      getpid(),
      inet_ntoa(paddr->sin_addr),
      ntohs(paddr->sin_port));

  _unused_(pid);

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
          log(stderr, "!select: %s\n", strerror(e));
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
              log(stderr, "!read: %s\n", strerror(errno));
              goto clean_exit;
            }

          if (0 == rc)
            {
              goto clean_exit;
            }

          log(stdout, "!read: xxx\n");
          s5_output(buf, rc);

          n = rc;
          FD_SET(cfd, &wfds);
        }

      if (FD_ISSET(cfd, &wfds))
        {
          FD_CLR(cfd, &wfds);

          if ((size_t) n == sizeof(s5_select_req_t))
            {
              req_select = (s5_select_req_t *) &buf;
              if (req_select->ver != S5_VER)
                {
                  log(stderr, "!socks: version: %d not support\n",
                      req_cmd->ver);
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

              n = 0;

            } /* select */
          else
            {
              req_cmd = (s5_cmd_req_t *) &buf;
              if (req_cmd->ver != S5_VER)
                {
                  log(stderr, "!socks: version: %d not support\n",
                      req_cmd->ver);
                  goto clean_exit;
                }

              s5_socks_cmd_reply(cfd, req_cmd, buf, n);

              switch (req_cmd->cmd)
                {
                case S5_CMD_CONNECT:

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
            } /* command */
        } /* write */


    }


 clean_exit:
  close(cfd);
  exit(rc);
}


static void
s5_socks_cmd_reply(int cfd, const s5_cmd_req_t *req, const char *buf,
                   ssize_t nbuf)
{
  int                 rc  =  0;
  pid_t               pid;
  struct sockaddr_in  pladdr;
  struct sockaddr_in  ppaddr;

  _unused_(rc);
  _unused_(pid);
  _unused_(cfd);
  _unused_(buf);
  _unused_(nbuf);

  switch (req->cmd)
    {
    case S5_CMD_CONNECT:
      _unused_(pladdr);
      _unused_(ppaddr);
      break;

      default:
        break;
    }

}

static void
s5_proxy_forward(int cfd, const struct sockaddr_in *caddr,
                 const struct sockaddr_in *paddr)
{
  int             rc    =  0;
  int             sfd;
  int             n, e;
  int             nfds  =  0;
  char            buf[BUF_MAX];
  pid_t           pid   =  0;
  fd_set          rfds, wfds;
  struct timeval  timeout;

  log(stdout, "!proxy[froward@%d]: from %s:%d, to %s:%d\n",
      getpid(),
      inet_ntoa(caddr->sin_addr),
      ntohs(caddr->sin_port),
      inet_ntoa(paddr->sin_addr),
      ntohs(paddr->sin_port));

  log(stdout, "!proxy[%d]: connecting ...\n", getpid());

  if (!opt_listen_only)
    {
      sfd = s5_connect(paddr);
      if (-1 == sfd)
        {
          goto clean_exit;
        }

      log(stdout, "!proxy[%d]: connected ...\n", getpid());

      pid = fork();
      if (-1 == pid)
        {
          log(stderr, "!fork: %s\n", strerror(errno));
        }
      else if (0 == pid)
        {
          s5_proxy_backward(cfd, sfd);
        }

    } /* !opt_listen_only */

  n = 0;
  FD_ZERO(&wfds);

  for (;;)
    {
      memcpy(&timeout, &opt_timeout, sizeof(timeout));

      FD_ZERO(&rfds);
      s5_fd_set(cfd, &rfds, &nfds);

      log(stdout, "!select[%d]: selecting %d ...\n", getpid(), cfd);

      rc = select(nfds, &rfds, NULL, NULL, &timeout);
      if (-1 == rc)
        {
          e = errno;
          log(stderr, "!select[%d]: %s\n", getpid(), strerror(e));
          goto clean_exit;
        }

      if (0 == rc)
        {
          goto clean_exit;
        }

      log(stdout, "!select[%d]: selected %d\n", getpid(), cfd);

      if (FD_ISSET(cfd, &rfds))
        {
          memset(buf, 0, sizeof(buf));

          rc = read(cfd, buf, sizeof(buf));
          if (-1 == rc)
            {
              log(stderr, "!read[%d]: %s\n", getpid(), strerror(errno));
              goto clean_exit;
            }

          if (0 == rc)
            {
              goto clean_exit;
            }

          if (opt_listen_only)
            {
              log(stdout, "!read[%d]: %s", getpid(), buf);
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
                  log(stderr, "!write[%d]: %s", getpid(), strerror(errno));
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

  log(stdout, "!proxy [backward:%d]: \n", getpid());

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
          log(stderr, "!select[%d]: %s\n", getpid(), strerror(e));
          goto clean_exit;
        }

      if (0 == rc)
        {
          goto clean_exit;
        }

      log(stdout, "!proxy[backward:%d]: [selected:%d] [r:%d|%d], [w:%d]\n",
          getpid(), rc, sfd, FD_ISSET(sfd, &rfds), cfd);

      if (FD_ISSET(sfd, &rfds))
        {
          memset(buf, 0, sizeof(buf));

          rc = read(sfd, buf, sizeof(buf));
          if (-1 == rc)
            {
              log(stderr, "!read[%d]: %s", getpid(), strerror(errno));
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
              log(stderr, "!write[%d]: %s", getpid(), strerror(errno));
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


static void
s5_fd_set(int fd, fd_set *fds, int *nfds)
{
  FD_SET(fd, fds);
  if (*nfds <= fd)
    {
      *nfds = fd + 1;
    }
}

static void
s5_output(const char *buf, size_t nbuf)
{
  FILE    *f  =  0;
  char     path[PATH_MAX];
  size_t   len;

  if (0 == getcwd(path, sizeof(path)))
    {
      perror(NULL);
      return;
    }

  len = strlen(path);
  sprintf(path + len, "/%d.out", getpid());

  f = fopen(path, "w");
  if (!f)
    {
      perror(NULL);
      return;
    }

  fwrite(buf, 1, nbuf, f);

  if (ferror(f))
    {
      perror(NULL);
      clearerr(f);
      goto clean_exit;
    }

 clean_exit:
  log(stdout, "!s5_output: %s\n", path);
  fclose(f);
}

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
          log(stderr, "!fork: %s\n", strerror(errno));
        }
      else if (0 == pid)
        {
          s5_proxy_forward(cfd, &caddr, paddr);
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
  int                 rc  =  0;
  int                 sfd, cfd;
  pid_t               pid;
  socklen_t           slen;
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
          log(stderr, "!fork: %s\n", strerror(errno));
        }

      if (0 == pid)
        {
          s5_socks_cmd(cfd, paddr);
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
                                 "hl:L:Kp:P:OT:Qo",
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
          opt_quiet = '\n';
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
  log(stdout, "# command line options @%d:\n"
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
      rc = s5_socks(&opt_listen_addr, &opt_proxy_addr);
    }


 clean_exit:
  return rc;
}


/* eof */
