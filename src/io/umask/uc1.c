#include <_io_.h>


/*
 * chmod doesn't using umask.
 *
 */


#define R_SR__R__ (S_IRUSR |S_ISUID | S_IRGRP | S_IROTH)


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  if (chmod(argv[1], R_SR__R__) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
