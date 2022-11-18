#include <_stdio_.h>
#include <stdio.h>
#include <stdarg.h>

#if !(NM_HAVE_RESTRICT_KEYWORD)
#  if (NM_HAVE___RESTRICT_KEYWORD)
#    define restrict __restrict
#  else
#    define restrict
#  endif
#endif

void
foo(const char *restrict format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);
}

int
main(int argc, char **argv) {
	switch (argc) {
	case 1:
		foo("%s\n", argv[0]);
		break;
	case 2:
		foo("%s, %s\n", argv[0], argv[1]);
		break;
	default:
		foo("no argument\n");
		break;
	}

	return 0;
}
