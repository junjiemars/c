#include <_lang_.h>
#include <stdio.h>

#ifndef MSVC
#  include <signal.h>
#  include <sys/wait.h>
#  include <unistd.h>

#define PRINT_FLAG(...) fprintf(stderr, "sig_flag = 0x%08x\n", __VA_ARGS__)

static volatile int sig_flag = 0x11;

void on_sigchld(int sig)
{
	_unused_(sig);
  fprintf(stderr, "^ on_sigchld\n");

	sig_flag += 0x1;
}
#endif  /* end of !MSVC */

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

#ifndef MSVC	
	pid_t pid;
	signal(SIGCHLD, on_sigchld);

  PRINT_FLAG(sig_flag);

	if (0 == (pid = fork()))
    {
      sig_flag += 0x2;
      return 0;
    }
	waitpid(pid, 0, 0);
	PRINT_FLAG(sig_flag);
#endif  /* end of !MSVC */
	
	return 0;
}
