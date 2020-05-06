#include <_io_.h>

#ifdef GCC
# ifndef __USE_XOPEN
#   define __USE_XOPEN
# endif
# ifndef _DEFAULT_SOURCE
#   define _DEFAULT_SOURCE
# endif
#endif

#if !defined(NM_HAVE_P_TMPDIR)
#  if defined(WINNT)
#    define P_tmpdir getenv("TMPDIR")
#  endif
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void
test_consts(void) {
	printf("P_tmpdir=%s\n", P_tmpdir);
	printf("L_tmpnam=%i\n", L_tmpnam);
	printf("TMP_MAX=0x%08x\n", TMP_MAX);
}

void
test_tmpfile(void) {
#if NM_HAVE_TMPFILE_FN
  FILE *out = tmpfile();
  if (!out) {
    perror("!panic");
    return;
  }
  fprintf(stdout, ">> fd:%i ...\n", fileno(out));
  fprintf(out, "test_tmpfile fn\n");
  if (ferror(out)) {
    perror("!panic");
  }
  fclose(out);
#endif
}

void
test_tmpnam(void) {
#if !NM_HAVE_MKSTEMP_FN
	char b1[L_tmpnam];
	strcpy(b1, tmpnam(0)); /* may be overwriten by next call */
	printf("tmpnam(0) = %s\n", b1);
	char b2[L_tmpnam];
	tmpnam(b2);
	printf("tmpnam(\"non-nil\") = %s\n", b2);
#endif
}

void
test_mkstemp(void) {
#if NM_HAVE_MKSTEMP_FN
	char t[L_tmpnam] = {};
  strcat(t, P_tmpdir);
  strcat(t, "/abcXXXXXX");
  
	int fd = mkstemp(t);
  if (-1 == fd) {
    perror("!panic");
    return;
  }
  
  FILE *out = fdopen(fd, "w");
  if (!out) {
    perror("!panic");
    return;
  }
  fprintf(stdout, ">> %s ...\n", t);
  fprintf(out, "test_mkstemp\n");
  if (ferror(out)) {
    perror("!panic");
  }
  fclose(out);
#endif
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	test_consts();
  test_tmpfile();
  test_mkstemp();
	test_tmpnam();

	return 0;
}
