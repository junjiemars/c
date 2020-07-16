#include "_uv_.h"
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define LOG(x) fprintf(stderr, (x))
#define LOGF(fmt, x) fprintf(stderr, #fmt, (x))

static struct option long_options[] = {
      {"help",    no_argument,         0, 'H'},
      {"host",    optional_argument,   0, 'h'},
      {"port",    optional_argument,   0, 'p'},
      {"head",    optional_argument,   0, 'I'},
      {"file",    optional_argument,   0, 'f'},
      {0,         no_argument,         0, '-'},
      {0,         0,                   0,  0 },
};


static char opt_host[NAME_MAX] = "127.0.0.1";
static long opt_port = 9696;
static char opt_head[NAME_MAX] = {0};
static char opt_file[NAME_MAX] = "abc";
static int  opt_stdin = 0;

void usage(const char*);
void on_connect(uv_stream_t*, int);
void on_close(uv_handle_t*);
void on_shutdown(uv_shutdown_t*, int);
void on_alloc(uv_handle_t*, size_t, uv_buf_t*);
void on_read(uv_stream_t*, ssize_t, const uv_buf_t*);
void on_write(uv_write_t*, int);

void
usage(const char *httpd) {
  printf("Usage: %s [OPTION]...\n", httpd);
  printf("\n");
  printf("A tiny http server, listen, accept and response what your want.\n");
  printf("  -H, --help             print this message\n");
  printf("  -h, --host             listen IP address, default 127.0.0.1\n");
  printf("  -p, --port             listen port, default 9696\n");
  printf("  -I, --head             response header file, default 9696\n");
  printf("  -f, --file             response data file\n");
}

void
on_connect(uv_stream_t *host, int status) {
  if (status < 0) {
    LOGF("!panic, connect error %s\n", uv_strerror(status));
    return;
  }

  uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(host->loop, client);

  int r = uv_accept(host, (uv_stream_t*) client);
  if (r) {
    uv_shutdown_t *shutdown = malloc(sizeof(uv_shutdown_t));
    uv_shutdown(shutdown, (uv_stream_t *) client, on_shutdown);
  }

  uv_read_start((uv_stream_t*) client, on_alloc, on_read);
}

void
on_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
	_unused_(handle);
  *buf = uv_buf_init(malloc(suggested_size), suggested_size);
}

void
on_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
  _unused_(handle);
  _unused_(nread);
  _unused_(buf);
  if (nread < 0) {
    LOG("read empty\n");
    uv_close((uv_handle_t*) handle, on_close);
    return;
  }
  uv_close((uv_handle_t*) handle, on_close);
  free(buf->base);
}

void
on_close(uv_handle_t *handle) {
  LOG("close connection\n");
  free(handle);
}

void
on_shutdown(uv_shutdown_t *shutdown, int status) {
	_unused_(status);
  uv_close((uv_handle_t *) shutdown->handle, on_close);
  free(shutdown);
}

void
on_write(uv_write_t* write_req, int status) {
	_unused_(status);
  uv_close((uv_handle_t *) write_req->handle, on_close);
  free(write_req);
}

int
main(int argc, char **argv) {
  int ch;
  while (-1 != (ch = getopt_long(argc, argv, "Hh:p:I:f:-", long_options, 0))) {
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
    case 'I':
      strncpy(opt_head, optarg, sizeof(opt_head));
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

  uv_loop_t *loop = uv_default_loop();

  uv_tcp_t host;
  struct sockaddr_in addr;
  int r = 0;

  uv_tcp_init(loop, &host);
  uv_ip4_addr(opt_host, opt_port, &addr);
  r = uv_tcp_bind(&host, (const struct sockaddr*)&addr, 0);
  if (r) {
    LOGF("!panic, bind error %s\n", uv_strerror(r));
    return 1;
  }

  r = uv_listen((uv_stream_t*) &host, opt_port, on_connect);
  if (r) {
    LOGF("!panic, listen error %s\n", uv_strerror(r));
    return 1;
  }
  return uv_run(loop, UV_RUN_DEFAULT);
}
