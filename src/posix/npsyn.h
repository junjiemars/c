/**
 * Nore Process Sync
 */

#ifndef _NPSYN_H_
#define _NPSYN_H_

#include <nustd.h>


int need_wait (void);
int tell_parent (pid_t pid);
int tell_child (pid_t pid);
int wait_parent (void);
int wait_child (void);

#endif /* _NPSYN_H_ */
