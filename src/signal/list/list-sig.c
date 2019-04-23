#include <_signal_.h>
#include <signal.h>
#include <stdio.h>

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	for (int i = 0; i < NSIG; i++) {
#ifdef DARWIN
		printf("[%02i] [%s] %s\n", i, sys_signame[i], sys_siglist[i]);
#elif LINUX
		printf("[%02i] [%s]\n", i, sys_siglist[i]);
#else
#endif
	}
	
	return 0;
}
