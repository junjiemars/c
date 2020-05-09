#include <_io_.h>

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

#include <stdio.h>
#include <string.h>

void
hex_out(const char *ss) {
  unsigned char c;
  while (0 != (c = *ss++)) {
    fprintf(stdout, "0x%02x ", c);
  }
  fprintf(stdout, "\n");
}

#if NM_HAVE_OPEN_FN && NM_HAVE_MMAP_FN
void
test_read(const char *file, size_t len) {
  int fd = open(file, O_RDONLY);
  if (-1 == fd) {
    perror("!panic");
    return;
  }

  char *m = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
  if (MAP_FAILED == m) {
    perror("!panic, mmap failed, caused by");
    goto clean_exit;
  }

  char buf[16];
  size_t offset = 0;
  memcpy(buf, m+offset, sizeof(buf)-1);

  fprintf(stdout, "read from %s@%zu\n====\n", file, offset);
  hex_out(buf);

  offset = 16;
  memcpy(buf, m+offset, sizeof(buf)-1);
  fprintf(stdout, "read from %s@%zu\n====\n", file, offset);
  hex_out(buf);
  
 clean_exit:
  if (munmap(m, len)) {
    perror("!panic, munmap failed, caused by");
  }
  close(fd);
}
#endif

int
main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stdout, "where the input file location and size\n");
    return 0;
  }

  const char *file = argv[1];
  size_t len = 0;
  if (0 >= sscanf(argv[2], "%zu", &len)) {
    perror("!panic");
    return 1;
  }
  
#if NM_HAVE_OPEN_FN
  test_read(file, len);
#endif
  
  return 0;
}
