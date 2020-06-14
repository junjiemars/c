#ifndef _CPU_H_
#define _CPU_H_

#include <nore.h>

#define _unused_(x) ((void)(x))

#include <time.h>
#define _time_(E, V) do {                       \
  clock_t _epoch_1_ = clock();                  \
  (E);                                          \
  V = (clock() - _epoch_1_);                    \
} while (0)


#endif /* end of _CPU_H_ */
