#include <uvl.h>


static uv_loop_t* loop;
static uv_getaddrinfo_t handle;

static void on_resolved(uv_getaddrinfo_t* handle, 
	int status, struct addrinfo* res) {
    _unused_(handle);
    _unused_(status);
	uv_freeaddrinfo(res);
}

int main(int argc, char* argv[]) {
	if (argc < 2) return 1;

	loop = uv_default_loop();
	int r = uv_getaddrinfo(loop, &handle, *&on_resolved, argv[1], 0, 0);
	if (r) {
		fprintf(stderr, "query dns failed: %s\n", uv_err_name(r));
		return r;
	}

	return uv_run(loop, UV_RUN_DEFAULT);
}
