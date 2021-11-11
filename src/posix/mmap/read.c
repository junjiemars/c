#include "_mmap_.h"
#include <stdio.h>
#include <string.h>


#if (NM_HAVE_MMAP)

void test_read(const char *file, size_t len);

void
test_read(const char *file, size_t len) {
  int fd = open(file, O_RDONLY);
  if (-1 == fd) {
    perror("!panic");
    return;
  }

  size_t offset = 0;
  char *m = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, offset);
  if (MAP_FAILED == m) {
    perror("!panic, mmap failed, caused by");
    goto clean_exit;
  }

  char buf[16];
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

#endif  /* end of (NM_HAVE_OPEN) */

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
  
#if (NM_HAVE_MMAP)
  test_read(file, len);
#endif
  
  return 0;
}
