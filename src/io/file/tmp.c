#include <_io_.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#ifdef GCC
#	ifndef __USE_SVID
#		define __USE_SVID 0x1122
#	endif
#	include <stdio.h>
#else
#	include <stdio.h>
#endif

#if defined(WINNT) && !defined(NM_HAVE_P_TMPDIR)
# define P_tmpdir getenv("TMPDIR")
#endif

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("P_tmpdir=%s\n", P_tmpdir);
	printf("L_tmpnam=%i\n", L_tmpnam);

	char *s = tmpnam(0);
	printf("tmpname(0) = %s\n", s);

	char nam[L_tmpnam];
	tmpnam(nam);
	printf("tmpnam(nam) = %s\n", nam);

	strncpy(nam, "xyz.", sizeof(nam));
	s = tempnam(P_tmpdir, nam);
	printf("tempnam(%s, \"xyz\") = %s\n", P_tmpdir, s);

	FILE *tf = tmpfile();
	if (!tf) {
		fprintf(stderr, "tmpfile() failed, %s\n", strerror(errno));
		goto error_exit;
	}

	fprintf(tf, "%s, tmp.c\n", argv[0]);
	goto clean_exit;

 error_exit:
	return 1;

 clean_exit:
	if (tf) {
		fclose(tf);
	}
}
