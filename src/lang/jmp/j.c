#include <_lang_.h>
#include <setjmp.h>
#include <stdio.h>

jmp_buf env;
volatile int flag = 0x11223344;

void a(void);
void b(volatile int*);
void c(volatile int*);

void
a(void) {
	int i;
	volatile int flag_in_stack = flag;
	
	printf("^setjmp()\n[flag=0x%x, flag_in_stack=0x%x]\n=> ", 
				 flag, flag_in_stack);
	if (0 != (i = setjmp(env))) {
		printf("\n$longjmp(0x%x)\n[flag=0x%x, flag_in_stack=0x%x]\n", 
					 i, flag, flag_in_stack);
	} else {
		printf("b() => ");
		b(&flag_in_stack);
	}
}

void 
b(volatile int *flag_in_stack) {
	printf("c() => ");
	c(flag_in_stack);
}

void
c(volatile int *flag_in_stack) {
	flag = 0x44332211;
	*flag_in_stack = flag;
	printf("longjmp() => ");
	longjmp(env, 0x1234);
}

int
main(int argc, char *argv[]) {
	_unused_(argc);
	_unused_(argv);
	a();	
}
