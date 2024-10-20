#ifndef PSYNC_H
#define PSYNC_H 1

#include <unistd.h>


int tell_wait (void);
int tell_parent (pid_t);
int wait_parent (void);
int tell_child (pid_t);
int wait_child (void);


#endif  /* end of PSYNC_H */
