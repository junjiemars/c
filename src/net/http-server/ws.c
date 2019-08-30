#include <_net_.h>
#include <getopt.h>
#include <http_parser.h>
#include <uv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LOG(x) fprintf(stdout, "%s", (x))
#define LOGF(fmt, x) fprintf(stdout, #fmt, (x))

#define RESPONSE                  \
  "HTTP/1.1 200 OK\r\n"           \
  "Content-Type: text/plain\r\n"  \
  "Content-Length: 12\r\n"        \
  "\r\n"                          \
  "Green Book!\n"

typedef struct {
  uv_tcp_t handle;
  http_parser parser;
} client_t;

static uv_tcp_t server;
static http_parser_settings parser_settings;

static void on_close(uv_handle_t *);
static void on_shutdown(uv_shutdown_t *, int);
static void on_alloc(uv_handle_t*, size_t, uv_buf_t*);
static void on_connect(uv_stream_t *, int);
static void on_read(uv_stream_t*, ssize_t, const uv_buf_t*);
static void on_write(uv_write_t*, int);
static int on_headers_complete(http_parser*);

void
on_close(uv_handle_t *handle) {
  client_t *client = (client_t *) handle->data;
  free(client);
}

void
on_shutdown(uv_shutdown_t *shutdown_req, int status) {
	_unused_(status);
  uv_close((uv_handle_t *) shutdown_req->handle, on_close);
  free(shutdown_req);
}

void
on_alloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
	_unused_(handle);
  buf->base = malloc(suggested_size);
  buf->len = suggested_size;
  assert(buf->base != NULL);
}

void
on_connect(uv_stream_t *server, int status) {
  assert(status == 0);

  client_t *client = malloc(sizeof(client_t));
  int r = uv_tcp_init(server->loop, &client->handle);
  assert(r == 0);
  client->handle.data = client;

  r = uv_accept(server, (uv_stream_t *) &client->handle);
  if (r) {
    uv_shutdown_t *shutdown_req = malloc(sizeof(uv_shutdown_t));
    uv_shutdown(shutdown_req, (uv_stream_t *) &client->handle, on_shutdown);
    assert(r == 0);
  }

  http_parser_init(&client->parser, HTTP_REQUEST);
  client->parser.data = client;
  r = uv_read_start((uv_stream_t *) &client->handle, on_alloc, on_read);
}

void
on_read(uv_stream_t* handle, ssize_t nread, const uv_buf_t* buf) {
  int r = 0;
  client_t *client = (client_t *) handle->data;

  if (nread >= 0) {
    size_t parsed = http_parser_execute(&client->parser, &parser_settings, buf->base, nread);

    if ((int)parsed < nread) {
      LOG("parse error\n");
      uv_close((uv_handle_t *) handle, on_close);
    }

  } else {
    if (nread == UV_EOF) {
      // do nothing
    } else {
      LOGF("read: %s\n", uv_strerror(nread));
    }

    uv_shutdown_t *shutdown_req = malloc(sizeof(uv_shutdown_t));
    r = uv_shutdown(shutdown_req, handle, on_shutdown);
    assert(r == 0);
  }
  free(buf->base);
}

void
on_write(uv_write_t* write_req, int status) {
	_unused_(status);
  uv_close((uv_handle_t *) write_req->handle, on_close);
  free(write_req);
}

int
on_headers_complete(http_parser* parser) {
  client_t *client = (client_t *) parser->data;

  uv_write_t *write_req = malloc(sizeof(uv_write_t));
  uv_buf_t buf = uv_buf_init(RESPONSE, sizeof(RESPONSE));
  int r = uv_write(write_req, (uv_stream_t *) &client->handle, &buf, 1, on_write);
  assert(r == 0);

  return 1;
}

void
server_init(uv_loop_t *loop, const char *host, int port, int backlog) {
  int r = uv_tcp_init(loop, &server);
  assert(r == 0);

  struct sockaddr_in addr;
  r = uv_ip4_addr(host, port, &addr);
  assert(r == 0);
  
  r = uv_tcp_bind(&server, (struct sockaddr *) &addr, 0);
  assert(r == 0);

  r = uv_listen((uv_stream_t *) &server, backlog, on_connect);
  assert(r == 0);
}

static char opt_host[128] = "127.0.0.1";
static int opt_port = 8080;

void
usage(const char *ws) {
  printf("Usage: %s [OPTION]...\n", ws);
	printf("\n");
	printf("A tiny-handy web server.\n");
	printf("  -h, --help             print this message\n");
	printf("  -a, --host             listen address, default is %s\n", opt_host);
	printf("  -p, --port             listen port, default is %i\n", opt_port);
}

static struct option long_options[] = {
			{"help",   no_argument,   0, 'h'},
			{"host",  no_argument,    0, 'a'},
			{"port",  no_argument,    0, 'p'},
			{0,        0,             0,  0 },
};

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

  int c;
  while (-1 != (c = getopt_long(argc, argv, "ha:p:", long_options, 0))) {
    switch (c) {
		case 'h':
			usage(argv[0]);
			return 0;
		case 'a':
			strcpy(opt_host, optarg);
			break;
		case 'p':
			if (1 != sscanf(optarg, "%i", &opt_port)) {
				printf("invalid argument '%s' of option '-p'\n", optarg);
				return -1;
			}
			break;
		default:
			usage(argv[0]);
			return -1;
    }
  }

	uv_loop_t *loop = uv_default_loop();

  parser_settings.on_headers_complete = on_headers_complete;
  server_init(loop, opt_host, opt_port, 128);

  int r = uv_run(loop, UV_RUN_DEFAULT);
  assert(r == 0);

  /* cleanup loop */

	return 0;
}
