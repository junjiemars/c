#include <_signal_.h>
#include <signal.h>
#include <stdio.h>

#if WINNT
#  include <windows.h>
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#  define getpid() _getpid()
void
psignal(int sig, const char *s) {
	static char *tbl[] = {
		"default",
		0,
		"interrupt",           /* SIGINT */
		0,
		"illegal instruction", /* SIGILL */
		0,
	};

	char *msg = (sig < 0 || sig >= sizeof(tbl)/sizeof(tbl[0]))
		? "unknown signal" : tbl[sig];
	if (0 == s || '\0' == s[0]) {
		fprintf(stderr, "%s\n", msg);
	} else {
		fprintf(stderr, "%s: %s\n", s, msg);
	}
}
#else
#  include <unistd.h>
#endif


static volatile int s_flag = 0;

void on_sigint(int sig) {
	psignal(sig, "on_sigint");
	s_flag = sig;
	/* continue put into pending signals */
	/* signal(sig, on_sigint); */
}

int main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("pid=%d\n", getpid());
	
	int n = 5;
	signal(SIGINT, on_sigint);

	do {
		fprintf(stderr, "sleeping...\n");
		if (s_flag) {
			break;
		}
		sleep(1);
	} while (--n > 0);

	return 0;
}
