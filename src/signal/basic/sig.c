#include <_signal_.h>
#include <signal.h>
#include <stdio.h>

#if WINNT
#  include <windows.h>
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#  define getpid() _getpid()
#else
#  include <unistd.h>
#endif


static volatile int s_flag = 0;

void on_sigint(int sig) {
	signal(sig, on_sigint);
	s_flag = sig;
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("pid=%d\n", getpid());
	
	int n = 5;
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
