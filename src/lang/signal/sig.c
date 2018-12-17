#include <_lang_.h>
#include <signal.h>
#include <stdio.h>

#if WINNT
#  include <windows.h>
#  define sleep(x) Sleep((x) * 1000)
#  include <process.h>
#  define getpid() _getpid()
#else
#  include <unistd.h>
#endif


static volatile int s_flag = 0;

void on_sigint(int sig) {
	if (SIGINT == sig) {
		s_flag = SIGINT;
	}
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("pid=%d\n", getpid());
	
	int n = 10;
	signal(SIGINT, on_sigint);

	do {
		printf("sleeping...\n");
		fflush(stdout);
		if (s_flag) {
			printf("on_sigint, exit.\n");
			fflush(stdout);
			break;
		}
		sleep(1);
	} while (--n > 0);

	return 0;
}
