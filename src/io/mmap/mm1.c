#include <_io_.h>
#include <stdio.h>

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


#if NM_HAVE_OPEN_FN && NM_HAVE_MMAP_FN
void
read_mmapped(const char *file, size_t len) {
  int fd = open(file, O_RDONLY);
  if (-1 == fd) {
    perror("!panic");
    return;
  }

  char *m = mmap(0, len, PROT_READ, MAP_FILE, fd, 0);
  if (!m) {
    perror("!panic");
    goto clean_exit;
  }

  char buf[16];
  if (-1 == read(fd, buf, sizeof(buf)-1)) {
    perror("!panic");
    goto clean_exit;
  }

  fprintf(stdout, "read from %s\n====\n", file);
  fprintf(stdout, "%s\n", buf);

 clean_exit:
  munmap(m, len);
  close(fd);
}
#endif

int
main(int argc, char **argv) {
  _unused_(argv);
  
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
  read_mmapped(file, len);
#endif
  
  return 0;
}
