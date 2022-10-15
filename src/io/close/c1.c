#include <_io_.h>

/*
 * 1. close(fd) just remove the fd's entry from the process table.
 *
 * 2. The kernel decrements the reference count of the file table
 * entry if the count > 1 or removes the entry when count = 1.
 *
 * 3. The kernel decrements the reference count of the inode table
 * entry if the count > 1 or frees the entry when count = 1.
 *
 * 4. Close all fd's entries in the process table when the process
 * exits.
 *
 */


#define ALPHA_L  "abc\n"


int
main(void)
{
  int fd;

  fd = dup(STDOUT_FILENO);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (close(STDOUT_FILENO) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (write(STDOUT_FILENO, ALPHA_L, _nof_(ALPHA_L)-1) != _nof_(ALPHA_L)-1)
    {
      perror("stdout");
    }

  if (write(fd, ALPHA_L, _nof_(ALPHA_L)-1) != _nof_(ALPHA_L)-1)
    {
      perror("stdout(dup)");
    }


  exit(EXIT_SUCCESS);
}
