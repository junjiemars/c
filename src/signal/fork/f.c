#include <_signal_.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

static volatile int sig_flag = 0x11;

void on_sigchld(int sig) {
	_unused_(sig);
	sig_flag += 0x1;
}

int
main(int argc, char **argv) {
	_unused_(argc);
	_unused_(argv);

	pid_t pid;
	signal(SIGCHLD, on_sigchld);

	if (0 == (pid = fork())) {
		sig_flag += 0x2;
		return 0;
	}
	waitpid(pid, 0, 0);
	printf("sig_flag = 0x%08x\n", sig_flag);
	
	return 0;
}
