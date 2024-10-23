#ifndef _PTYS_H_
#define _PTYS_H_

#include <stddef.h>
#include <unistd.h>

int pty_open_master (char *name, size_t namesz);
int pty_open_slave (char *name);
pid_t pty_fork (int *fdp, char *name, size_t namesz);

#endif /* end of _PTYS_H_ */
