#include <_lang_.h>
#include <setjmp.h>
#include <stdio.h>

/* https://en.wikipedia.org/wiki/Setjmp.h */

static void throw(jmp_buf*);
static void f(void);
static void g(jmp_buf*);

static volatile int exception_type;

#define INDENT_0 ""
#define INDENT_1 "  "
#define INDENT_2 INDENT_1 INDENT_1


void f(void)
{
	jmp_buf exception_env;
	exception_type = 0;

	switch (setjmp(exception_env))
    {
    case 0:
      printf("%s g()...\n", INDENT_0);
      g(&exception_env);
      break;
    case 0x11220000:
      printf("%s catch exception: 0x%x\n", INDENT_0, 0x11220000);
      break;
    default:
      break;
    }
}

void g(jmp_buf *env)
{
	jmp_buf local_env;
	printf("%s g()\n", INDENT_1);
	
	switch (setjmp(local_env))
    {
    case 0x11000000:
      exception_type |= 0x00220000;
      printf("%s catch throw(), exception_type=0x%x, jump to 0x%x\n",
             INDENT_1, 0x11000000, exception_type);
    default:
      longjmp(*env, exception_type);
      break;
    case 0:
      printf("%s throw()...\n", INDENT_1);
      throw(&local_env);
      /* never reached */
      break;
    }

	/* never reached when throw() jmp */
	/* fputs("leaving g()...\n", stdout); */
}

void throw(jmp_buf *env)
{
	printf("%s throw()\n", INDENT_2);
	longjmp(*env, exception_type |= 0x11000000);
}


int main(int argc, char *argv[])
{
	_unused_(argc);
	_unused_(argv);

	f();
	
	return 0;
}
