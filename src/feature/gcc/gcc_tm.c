#include <_feature_.h>
#include <stdio.h>

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

#ifdef __STRICT_ANSI__
	printf("#define __STRICT_ANSI__\n");
#endif

#ifdef _POSIX_SOURCE
	printf("#define _POSIX_SOURCE\n");
#endif

#ifdef _POSIX_C_SOURCE
	printf("#define _POSIX_C_SOURCE %ldL\n", (long) _POSIX_C_SOURCE);
#endif

#ifdef _ISOC99_SOURCE
	printf("#define _ISOC99_SOURCE\n");
#endif

#ifdef _ISOC11_SOURCE
	printf("#define _ISOC11_SOURCE\n");
#endif

#ifdef _XOPEN_SOURCE
	printf("#define _XOPEN_SOURCE %d\n", _XOPEN_SOURCE);
#endif

#ifdef _XOPEN_SOURCE_EXTENDED
	printf("_XOPEN_SOURCE_EXTENDED defined\n");
#endif

#ifdef _LARGEFILE64_SOURCE
	printf("_LARGEFILE64_SOURCE defined\n");
#endif

#ifdef _FILE_OFFSET_BITS
	printf("#define _FILE_OFFSET_BITS %d\n", _FILE_OFFSET_BITS);
#endif

#ifdef _BSD_SOURCE
	printf("#define _BSD_SOURCE\n");
#endif

#ifdef _SVID_SOURCE
	printf("#define _SVID_SOURCE\n");
#endif

#ifdef _DEFAULT_SOURCE
	printf("_DEFAULT_SOURCE defined\n");
#endif

#ifdef _ATFILE_SOURCE
	printf("#define _ATFILE_SOURCE\n");
#endif

#ifdef _GNU_SOURCE
	printf("#define _GNU_SOURCE\n");
#endif

#ifdef _REENTRANT
	printf("_REENTRANT defined\n");
#endif

#ifdef _THREAD_SAFE
	printf("_THREAD_SAFE defined\n");
#endif

#ifdef _FORTIFY_SOURCE
	printf("#define _FORTIFY_SOURCE\n");
#endif

	return 0;
}
