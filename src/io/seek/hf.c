#include "_io_.h"


/*
 * Couting the holes and the data;
 *
 */



int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", argv[1]);
      exit(EXIT_FAILURE);
    }

#if defined(_PC_MIN_HOLE_SIZE)
  printf("_PC_MIN_HOLE_SIZE: %li\n", (long long) _PC_MIN_HOLE_SIZE);
#else
  printf("_PC_MIN_HOLE_SIZE: (no symbol)\n");

#endif  /* _PC_MIN_HOLE_SIZE */


#if defined(SEEK_DATA) && defined(SEEK_HOLE)

  int    fd;
  off_t  off_s, off_e;
  off_t  n_data, n_hole;

  fd = open(argv[1], O_RDONLY);
  if (fd == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  off_s = 0;
  off_e = 0;
  n_data = 0;
  n_hole = 0;

  while (1 == 1)
    {
      off_s = lseek(fd, off_e, SEEK_DATA);
      if (off_s == -1)
        {
          break;
        }

      n_hole += (off_s - off_e);

      off_e = lseek(fd, off_s, SEEK_HOLE);
      if (off_e == -1)
        {
          break;
        }

      n_data += (off_e - off_s);

    }

  printf("data:  % 16li\n"
         "hole:  % 16li\n"
         "------------\n"
         "total: % 16li\n",
         n_data, n_hole, n_data + n_hole);


#else
  printf("!panic: finding hole unsupported.\n");

#endif

  exit(EXIT_SUCCESS);
}
