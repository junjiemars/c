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

int 
main(int argc, const char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	narrow();
	broaden();
}
