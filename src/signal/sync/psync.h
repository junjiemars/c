#ifndef _PSYNC_H
#define _PSYNC_H 1

#include <unistd.h>

int tell_wait (void);
int tell_parent (pid_t pid);
int wait_parent (void);
int tell_child (pid_t pid);
int wait_child (void);

#endif
