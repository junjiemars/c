#include <_lang_.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#ifdef MSVC
#  pragma warning(disable: 4996)
#  include <windows.h>
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#  define getpid() _getpid()
static void
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

static void
on_sigint_stop(int sig) {
	psignal(sig, "on_sigint_stop");
	s_flag = sig;
}

static void
on_sigint_continue(int sig) {
	psignal(sig, "on_sigint_continue");
	/* continue put into pending signals */
	signal(sig, on_sigint_stop);
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	printf("pid=%d\n", getpid());
	
	int n = 10;
	signal(SIGINT, on_sigint_continue);

	do {
		if (s_flag) {
			fprintf(stderr, "stop, s_flag = %i\n", s_flag);
			break;
		}
		if (6 == n /* 5th */) {
			int r = raise(SIGINT);
			if (r) {
				perror("raise SIGINT failed");
			}
		}
		fprintf(stderr, "sleeping 1s ...\n");
		sleep(1);
	} while (--n > 0);

	return 0;
}
