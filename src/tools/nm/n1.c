#include <_tools_.h>

int global_var;
int global_var_init = 0x11;

static int static_var;
static int static_var_init = 0x22;

static int
static_fn(void) {
	return static_var + static_var_init;
}

int
global_fn(int x) {
	int z;
	static int local_static_var;
	static int local_static_var_init = 0x22;
	z = x * 10;
	return z + local_static_var + local_static_var_init;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	static_fn();
	
	return 0;
}
