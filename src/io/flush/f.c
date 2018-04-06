#include <_io_.h>
#include <stdio.h>

#if !defined(NM_HAVE_FPURGE_FN) && defined(NM_HAVE___FPURGE_FN)

#include <stdio_ext.h>
#define fpurge(x) __fpurge((x))

#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	/* int i = 1, j = 0; */
	/* printf("before: i/j = %i/%i", i, j); */
	/* if not call fflush() here, the output of printf() may not be print */
	/* fflush(stdout); */
	/* i = i/j; */

	int ch = fgetc(stdin);
	fprintf(stdout, "[0] %c\n", ch);
	ch = fgetc(stdin);
	fprintf(stdout, "[1] %c\n", ch);

	fpurge(stdin);
	
	ch = fgetc(stdin);
	fprintf(stdout, "[2] %s\n", EOF == ch ? "EOF" : "!EOF");
}
