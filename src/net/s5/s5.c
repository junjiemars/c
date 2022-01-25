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


#define log(x, ...)                             \
  if (0 == opt_quiet)                           \
    {                                           \
      fprintf(x, __VA_ARGS__);                  \
    }


typedef struct s5_auth_req_s {
  uint8_t  ver;
  uint8_t  n;
  uint8_t  methods;
} s5_auth_req_t;

typedef struct s5_req_s {
  uint8_t ver;
  uint8_t cmd;
  uint8_t rsv;
  uint8_t atyp;
} s5_req_t;


#if !(NDEBUG)
typedef void (*on_signal)(int);
static void on_signal_segv(int sig);
#endif  /* NDEBUG */


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
  printf("  -p, --port     listen port, default is %d\n",
         opt_port);
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
          rc = 1;
          goto clean_exit;
        default:
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
  rc = 0;

 clean_exit:
  return rc;
}


/* eof */
