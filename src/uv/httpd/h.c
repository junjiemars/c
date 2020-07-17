#include "_uv_.h"
#include "parser/http_parser.h"
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <inttypes.h>

#define LOG(...) do {                                     \
    (void)(opt_verbose && fprintf(stderr, __VA_ARGS__));  \
} while (0)

static struct option long_options[] = {
      {"help",    no_argument,         0, 'H'},
      {"host",    optional_argument,   0, 'h'},
      {"port",    optional_argument,   0, 'p'},
      {"head",    optional_argument,   0, 'I'},
      {"file",    optional_argument,   0, 'f'},
      {"verbose", no_argument,         0, 'v'},
      {0,         no_argument,         0, '-'},
      {0,         0,                   0,  0 },
};

static char opt_host[NAME_MAX] = "127.0.0.1";
static long opt_port = 9696;
static char opt_head[NAME_MAX] = {0};
static char opt_file[NAME_MAX] = "abc";
static int  opt_verbose = 0;
static int  opt_stdin = 0;

static uv_loop_t *loop;
static uv_tcp_t host;

static http_parser_settings parser_settings;

static uv_process_t cgi_req;
static uv_process_options_t cgi_opt;


void usage(const char*);
void on_connect(uv_stream_t*, int);
void on_close(uv_handle_t*);
void on_shutdown(uv_shutdown_t*, int);
void on_alloc(uv_handle_t*, size_t, uv_buf_t*);
void on_read(uv_stream_t*, ssize_t, const uv_buf_t*);
void on_write(uv_write_t*, int);

void cgi_exe(uv_tcp_t*);
void on_cgi_close(uv_process_t*, int64_t, int);

int on_url(http_parser*, const char*, size_t);
int on_body(http_parser*, const char*, size_t);
int on_message_complete(http_parser*);

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
  printf("  -v, --verbose          verbose output\n");
}

void
on_connect(uv_stream_t *host, int status) {
  if (status < 0) {
    LOG("!panic, connect error %s\n", uv_strerror(status));
    return;
  }

  uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
  uv_tcp_init(host->loop, client);

  int r = uv_accept(host, (uv_stream_t*) client);
  if (r) {
    uv_shutdown_t *shutdown = malloc(sizeof(uv_shutdown_t));
    uv_shutdown(shutdown, (uv_stream_t *) client, on_shutdown);
    return;
  }
  
  struct sockaddr_in addr;
  int addr_len;
  char addr_buf[32];
  uv_tcp_getpeername(client, (struct sockaddr*) &addr, &addr_len);
  uv_ip4_name(&addr, &addr_buf[0], addr_len);
  LOG("#accepted from %s\n", addr_buf);

  uv_read_start((uv_stream_t*) client, on_alloc, on_read);
}

void
on_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
	_unused_(handle);
  *buf = uv_buf_init(malloc(suggested_size), suggested_size);
}

void
on_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
  if (nread < 0) {
    LOG("read empty\n");
    uv_close((uv_handle_t*) handle, on_close);
    return;
  }
  LOG("#read (%li bytes) ...\n%s\n", nread, buf->base);

  http_parser parser;
  parser.data = handle;
  http_parser_init(&parser, HTTP_REQUEST);

  size_t parsed = http_parser_execute(&parser, &parser_settings, buf->base, nread);
  if ((ssize_t)parsed != nread) {
    LOG("!panic, parse error: %s\n", "xxx");
  }
  /* cgi_exe((uv_tcp_t*) handle); */
  char *s1 = "HTTP/2 200 OK \r\n"
    "content-type: text/html; charset=utf-8 \r\n"
    "Accept-Ranges: bytes \r\n\r\n"
    "<!DOCTYPE html><html><body>abc</body></html>";

  uv_buf_t resp[] = {
    { .base = s1, .len = strlen(s1)+1 }
  };
  uv_write_t w;
  int r = uv_write(&w, handle, &resp[0], 1, 0);
  if (r) {
    LOG("!panic, write error: %s\n", uv_strerror(r));
  }

  uv_close((uv_handle_t*) handle, on_close);
  free(buf->base);
}

void
on_close(uv_handle_t *handle) {
  LOG("#closed\n");
  free(handle);
}

void
on_shutdown(uv_shutdown_t *shutdown, int status) {
	_unused_(status);
  uv_close((uv_handle_t *) shutdown->handle, on_close);
  LOG("#shutdown\n");
  free(shutdown);
}

void
on_write(uv_write_t* write_req, int status) {
	_unused_(status);
  uv_close((uv_handle_t *) write_req->handle, on_close);
  free(write_req);
}

void
on_cgi_close(uv_process_t *req, int64_t exit_status, int term_signal) {
  LOG("#cgi exited (status:%" PRId64 ", signal:%d)\n",
      exit_status, term_signal);

  uv_close((uv_handle_t*) req->data, 0);
  uv_close((uv_handle_t*) req, 0);
}
void
cgi_exe(uv_tcp_t *client) {
  char *args[2];
  args[0] = "./cgi.c";
  args[1] = 0;

  cgi_opt.stdio_count = 3;
  uv_stdio_container_t ios[3];
  ios[0].flags = UV_IGNORE;
  ios[1].flags = UV_INHERIT_STREAM;
  ios[1].data.stream = (uv_stream_t*) client;
  ios[2].flags = UV_IGNORE;

  cgi_opt.stdio = ios;
  cgi_opt.exit_cb = on_cgi_close;
  cgi_opt.file = args[0];
  cgi_opt.args = args;
  cgi_req.data = (void*) client;

  int r = uv_spawn(loop, &cgi_req, &cgi_opt);
  if (r) {
    LOG("!panic, spawn cgi error: %s\n", uv_strerror(r));
    return;
  }
}

int
on_url(http_parser *parser, const char *at, size_t length) {
  _unused_(parser);
  char *url = malloc(length+1);
  strncpy(url, at, length);
  
  free(url);
  return 0;
}

int
on_body(http_parser *parser, const char *at, size_t length) {
  _unused_(parser);
  _unused_(at);
  _unused_(length);
  return 0;
}

int
on_message_complete(http_parser *parser) {
  _unused_(parser);
  return 0;
}

int
main(int argc, char **argv) {
  int ch;
  while (EOF != (ch = getopt_long(argc, argv,
                                  "Hh:p:I:f:v-", long_options, 0))) {
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
    case 'v':
      ++opt_verbose;
      break;
		case '-':
			++opt_stdin;
			break;
		default:
			usage(argv[0]);
			return -1;
    }
  }

  /* parser_settings.on_url = on_url; */
  /* parser_settings.on_message_begin = on_message_begin; */
  /* parser_settings.on_headers_complete = on_headers_complete; */
  parser_settings.on_message_complete = on_message_complete;
  /* parser_settings.on_header_field = on_header_field; */
  /* parser_settings.on_header_value = on_header_value; */
  /* parser_settings.on_body = on_body; */

  loop = uv_default_loop();

  struct sockaddr_in addr;
  int r = 0;

  uv_tcp_init(loop, &host);
  uv_ip4_addr(opt_host, opt_port, &addr);
  r = uv_tcp_bind(&host, (const struct sockaddr*)&addr, 0);
  if (r) {
    LOG("!panic, bind error %s\n", uv_strerror(r));
    return 1;
  }

  r = uv_listen((uv_stream_t*) &host, opt_port, on_connect);
  if (r) {
    LOG("!panic, listen error %s\n", uv_strerror(r));
    return 1;
  }
  LOG("#listen on %s:%li ...\n", opt_host, opt_port);

  return uv_run(loop, UV_RUN_DEFAULT);
}
