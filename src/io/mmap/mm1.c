#include <_io_.h>
#include <stdio.h>

#if DARWIN
#  include <fcntl.h>
#  include <unistd.h>
#  include <sys/mman.h>
#endif

#if NM_HAVE_OPEN_FN && NM_HAVE_MMAP_FN
void
read_mmapped(const char *file, size_t len) {
  int fd = open(file, O_RDONLY);
  if (fd <= 0) {
    perror("!panic");
    return;
  }

  const char *m = mmap(0, len, PROT_READ, MAP_FILE, fd, 0);
  if (!m) {
    perror("!panic");
    goto clear_exit;
  }

 clear_exit:
  close(fd);
}
#endif

int
main(int argc, char **argv) {
  _unused_(argv);
  
  if (argc < 3) {
    fprintf(stdout, "where the input file location\n");
    return 0;
  }
  
#if NM_HAVE_OPEN_FN
  read_mmapped(argv[1], 1024*2);
#endif
  
  return 0;
}
