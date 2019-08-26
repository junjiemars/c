#include <_io_.h>

#ifdef GCC
# ifndef __USE_XOPEN
#   define __USE_XOPEN
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
test_tmpnam(void) {
	char b1[L_tmpnam];
	strcpy(b1, tmpnam(0)); /* may be overwriten by next call */
	printf("tmpnam(0) = %s\n", b1);
	char b2[L_tmpnam];
	tmpnam(b2);
	printf("tmpnam(\"non-nil\") = %s\n", b2);
}

/* void */
/* test_mkstemp(void) { */
/* 	char t[L_tmpnam << 4] = "vviviiXXXXXX"; */
/* 	int fd = mkstemp(t); */
/* 	_unused_(t); */
/* 	_unused_(fd); */
/* } */

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	test_consts();
	test_tmpnam();
	/* test_mkstemp(); */

 /* 	char *s = tmpnam(0); */
 /* 	printf("tmpname(0) = %s\n", s); */

 /* 	char nam[L_tmpnam + sizeof(void*)]; */
 /* 	tmpnam(nam); */
 /* 	printf("tmpnam(nam) = %s\n", nam); */

 /* 	strncpy(nam, "xyz.", sizeof(nam)); */
 /* 	s = tempnam(P_tmpdir, nam); */
 /* 	printf("tempnam(%s, \"xyz\") = %s\n", P_tmpdir, s); */

 /* 	FILE *tf = tmpfile(); */
 /* 	if (!tf) { */
 /* 		perror("call tmpfile() failed"); */
 /* 		goto error_exit; */
 /* 	} */

 /* 	fprintf(tf, "%s, tmp.c\n", argv[0]); */
 /* 	goto clean_exit; */

 /* error_exit: */
 /* 	return 1; */

 /* clean_exit: */
 /* 	if (tf) { */
 /* 		fclose(tf); */
 /* 	} */
	return 0;
}
