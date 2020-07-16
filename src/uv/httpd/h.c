#include "_uv_.h"
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

static struct option long_options[] = {
      {"help",  no_argument,         0, 'H'},
      {"host",  optional_argument,   0, 'h'},
      {"port",  optional_argument,   0, 'p'},
      {"file",  optional_argument,   0, 'f'},
      {0,       no_argument,         0, '-'},
      {0,       0,                   0,  0 },
};

static char opt_host[255] = "127.0.0.1";
static long opt_port = 9292;
static char opt_file[255] = "abc";
static int  opt_stdin = 0;

void usage(const char*);

void
usage(const char *httpd) {
  printf("Usage: %s [OPTION]...\n", httpd);
  printf("\n");
  printf("A tiny http server, listen and response what your want.\n");
  printf("  -H, --help             print this message\n");
  printf("  -h, --host             host address, default 127.0.0.1\n");
  printf("  -p, --port             listen on, default 9292\n");
  printf("  -f, --file             response file\n");
}


int
main(int argc, char **argv) {
  int ch;
  while (-1 != (ch = getopt_long(argc, argv, "Hh:p:f:-", long_options, 0))) {
    switch (ch) {
		case 'H':
			usage(argv[0]);
			return 0;
		case 'h':
			strncpy(opt_host, optarg, sizeof(opt_host));
			break;
		case 'p':
      opt_port = atol(optarg);
			break;
		case 'f':
      strncpy(opt_file, optarg, sizeof(opt_file));
			break;
		case '-':
			opt_stdin++;
			break;
		default:
			usage(argv[0]);
			return -1;
    }
  }

  return 0;
}
