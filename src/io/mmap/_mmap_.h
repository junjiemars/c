#ifndef _MMAP_H_
#define _MMAP_H_

#if DARWIN
#  include <fcntl.h>
#  include <unistd.h>
#  include <sys/mman.h>
#elif LINUX
#  include <sys/types.h>
#  include <sys/stat.h>
#  include <fcntl.h>
#  include <unistd.h>
#  ifndef __USE_MISC
#    define __USE_MISC 1
#  endif
#  include <sys/mman.h>
#endif


#endif /* end of _MMAP_H_ */
