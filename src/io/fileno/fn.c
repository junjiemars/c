#include <_io_.h>

#ifdef GCC
#  ifndef _POSIX_C_SOURCE
#    define _POSIX_C_SOURCE 1
#  endif
#endif
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("stdin=%d, stdout=%d, stderr=%d\n",
				 fileno(stdin),
				 fileno(stdout),
				 fileno(stderr));

	FILE *out = fdopen(fileno(stdout), "w");
	if (!out) {
		perror(0);
		return 1;
	}
	fprintf(out, "end of %s\n", argv[0]);

#ifdef MSVC
	/* fclose stdout should: */
  /* Security check failure or stack buffer overrun - code c0000409 */
#else
	fclose(out);
#endif

	return 0;
}
