#include "_mmap_.h"
#include <stdio.h>
#include <string.h>


#if (NM_HAVE_OPEN) && (NM_HAVE_MMAP)
void
test_write(const char *file, size_t len)
{
  int fd = open(file, O_RDWR);
  if (-1 == fd)
    {
      perror("!panic, open failed, caused by");
      return;
    }

  size_t offset = 0;
  char *m = mmap(0, len, PROT_WRITE, MAP_SHARED, fd, offset);
  if (MAP_FAILED == m)
    {
      perror("!panic, mmap failed, caused by");
      goto clean_exit;
    }

  char buf[16] = "aabbccdd";
  if (-1 == write(fd, buf, sizeof(buf)))
    {
      perror("!panic, write failed, caused by");
      goto clean_exit;
    }
  fprintf(stdout, "write to %s@%zu\n====\n", file, offset);
  hex_out(buf);

 clean_exit:
  if (munmap(m, len))
    {
      perror("!panic, munmap failed, caused by");
    }
  close(fd);
}
#endif

int
main(int argc, char **argv)
{
  if (argc < 3)
    {
      fprintf(stdout, "where the input file location and size\n");
      return 0;
    }

  const char *file = argv[1];
  size_t len = 0;
  if (0 >= sscanf(argv[2], "%zu", &len))
    {
      perror("!panic, sscanf failed, caused by");
      return 1;
    }

#if NM_HAVE_OPEN
  test_write(file, len);
#endif

  return 0;
}
