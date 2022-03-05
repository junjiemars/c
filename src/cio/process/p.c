#include <_cio_.h>

#if MSVC
#  if !(NM_HAVE_POPEN_FN) && (NM_HAVE__POPEN_FN)
#    define popen  _popen
#    define pclose _pclose
#  endif
#  define COMMAND_LS "dir"
#else
#  define COMMAND_LS "ls"
#endif

#if (GCC) && (NM_HAVE_POPEN_FN)
#  ifndef _GNU_SOURCE
#    define _GNU_SOURCE 1
#  endif
#endif

#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#if (NM_HAVE_POPEN_FN) || (NM_HAVE__POPEN_FN)
	fprintf(stdout, "popen process i/o\n");
	fprintf(stdout, "--------------------\n");

	FILE* out = popen(COMMAND_LS, "r");
	if (!out) {
		return ferror(out);
	}

	char s[512];
	while (0 != fgets(s, sizeof(s), out)) {
		printf("%s", s);
	}
	if (feof(out)) {
		fprintf(stdout, "!sucess\n");
	} else {
		fprintf(stderr, "!panic: ferror(out) = %d\n", ferror(out));
	}
	pclose(out);
#else
	fprintf(stdout, "!panic: popen fn no found\n");
#endif

	return 0;
}
