#include "_uv_.h"

static uv_loop_t* loop;

static void
on_resolved(uv_getaddrinfo_t* resolver, 
            int status,
            struct addrinfo* res) {
	_unused_(resolver);
	_unused_(status);
  
  if (status < 0) {
    fprintf(stderr, "!panic, failed on_resolved, caused by: %s\n",
            uv_err_name(status));
    return;
  }

  struct addrinfo *p = res;
  while (p) {
    char a[INET_ADDRSTRLEN+1] = {0};
    uv_ip4_name((struct sockaddr_in*)p->ai_addr, a, INET_ADDRSTRLEN);
    fprintf(stderr, "%s\n", a);
    p = p->ai_next;
	}

	uv_freeaddrinfo(res);
}

int
main(int argc, char **argv) {
	if (argc < 2) {
    fprintf(stderr, "where the target domain?\n");
    return 0;
  }

	loop = uv_default_loop();

  struct addrinfo hints;
  hints.ai_family = PF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = 0;
  
  uv_getaddrinfo_t resolver;
  fprintf(stderr, "resolving %s ...\n", argv[1]);
  
	int r = uv_getaddrinfo(loop,
                         &resolver,
                         on_resolved,
                         argv[1],
                         "53",
                         &hints);
	if (r) {
		fprintf(stderr, "resolve dns failed: %s\n", uv_err_name(r));
		return r;
	}

	return uv_run(loop, UV_RUN_DEFAULT);
}
