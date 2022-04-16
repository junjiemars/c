#include "_io_.h"


#define RRR (S_IRUSR | S_IRGRP | S_IROTH)


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  if (chmod(argv[1], RRR) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  exit(EXIT_SUCCESS);
}
