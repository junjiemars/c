#include <_x86_.h>

void 
narrow() {
	int i;
	char c;
	i = 0x11223344;
	c = i;	
}

void
broaden() {
	int i;
	char c;
	c = -1;
	i = c;
}

void
int_float() {
	int i;
	float f;
	i = 128;
	f = i;
}

void
float_int() {
	int i;
	float f;
	f = 3.1415;
	i = f;
}

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	narrow();
	broaden();

	int_float();
	float_int();
}
