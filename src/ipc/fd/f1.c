#include "_ipc_.h"

#define _X_ "XXX\n"
#define _Z_ "ZZZ\n"

int
main (void)
{
	pid_t pid;
	int fd[2] = {0, 1};

	if ((pid = fork ()) == -1)
	  {
			exit(1);
		}
	else if (pid == 0)
		{
			write (fd[1], _X_, sizeof (_X_)-1); 
			exit (0);
    }
	else
		{
			write (fd[1], _Z_, sizeof (_Z_)-1);
			waitpid (pid, NULL, 0);
			exit (0);
		}

  return 0;
}
