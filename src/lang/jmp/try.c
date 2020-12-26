#include <_lang_.h>
#include <setjmp.h>
#include <stdio.h>

/* https://en.wikipedia.org/wiki/Setjmp.h */

static void throw(jmp_buf*);
static void f(void);
static void g(jmp_buf*);

static volatile int exception_type;


void f(void) {
	jmp_buf exception_env;
	exception_type = 0;

	switch (setjmp(exception_env)) {
	case 0:
		fputs("calling g()...\n", stdout);
		g(&exception_env);
		break;
	case 0x11220000:
		printf("catch exception: 0x%x\n", 0x11220000);
		break;
	default:
		break;
	}
}

void g(jmp_buf *env) {
	jmp_buf local_env;
	fputs("entering g()...\n", stdout);
	
	switch (setjmp(local_env)) {
	case 0x11000000:
		exception_type |= 0x00220000;
		printf("throw(), exception_type=0x%x remapping to 0x%x",
					 0x11000000, exception_type);
	default:
		longjmp(*env, exception_type);
		break;
	case 0:
		fputs("calling throw()...\n", stdout);
		throw(&local_env);
		/* never reached */
		break;
	}

	/* never reached when throw() jmp */
	/* fputs("leaving g()...\n", stdout); */
}

void throw(jmp_buf *env) {
	fputs("entering throw()...\n", stdout);
	longjmp(*env, exception_type |= 0x11000000);
}


int main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);

	f();
	
	return 0;
}
