#include "_io_.h"

/*
 * Tom Duff is the author of /dev/fd feature and Duff Device.
 *
 *
 */


int
main(int argc, char *argv[])
{
  int           fd;
  char         *dev  =  "/dev/fd/0";

  if (argc > 1)
    {
      dev = argv[1];
    }

  if ((fd = open(dev, O_RDONLY)) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
