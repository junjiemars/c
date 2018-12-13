#include <_lang_.h>
#include <setjmp.h>
#include <stdio.h>

#define X_NO  0x11223344

void throw(jmp_buf *env) {
	longjmp(*env, X_NO);
}

int f(void) {
	jmp_buf env;
	int x;
	
	switch (setjmp(env)) {
	case 0:
		printf("throw exception: 0x%x\n", X_NO);
		throw(&env);
		break;
	case X_NO:
		printf("catch exception: 0x%x\n", X_NO);
		break;
	}

	return x;
}


int main(int argc, char **argv[]) {
	_unused_(argc);
	_unused_(argv);

	f();
	
	return 0;
}
