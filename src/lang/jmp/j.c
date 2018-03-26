#include <_lang_.h>
#include <setjmp.h>
#include <stdio.h>

void b(jmp_buf);
void c(jmp_buf);

int
a() {
	jmp_buf env;
	int i;

	printf("^setjmp() => ");
	if (0 != (i = setjmp(env))) {
		printf("$longjmp(0x%x)\n", i);
		return i;
	} else {
		printf("b() => ");
		b(env);
		return 0;
	}
}

void 
b(jmp_buf env) {
	printf("c() => ");
	c(env);
}

void
c(jmp_buf env) {
	printf("longjmp() => ");
	longjmp(env, 0x1234);
}

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);
	a();	
}
