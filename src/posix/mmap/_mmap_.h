#ifndef _MMAP_H_
#define _MMAP_H_

#include "norstd.h"

#if (DARWIN)
#  include <fcntl.h>
#  include <sys/mman.h>
#elif (LINUX)
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <fcntl.h>
#  ifndef __USE_MISC
#    define __USE_MISC 1
#  endif
#  include <sys/mman.h>
#endif

#include <stdio.h>

void
hex_out(const char *ss) {
  unsigned char c;
  while (0 != (c = *ss++)) {
    fprintf(stdout, "0x%02x ", c);
  }
  fprintf(stdout, "\n");
}


#endif /* end of _MMAP_H_ */
