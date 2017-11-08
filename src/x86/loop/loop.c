#include <_x86_.h>


void
for_loop() {
	char ch;
	int i;
	
	for (i = 0; i < 10; i++) {
		ch = 'a';
	}
	i = 25;
}

void
while_loop() {
	char ch;
	int i;

	i = 0;
	while (i < 10) {
		ch = 'a';
		i++;
	}
	i =25;
}

int
main(int argc, char* argv[]) {
	_unused_(argc);
	_unused_(argv);

	for_loop();
	while_loop();
}

