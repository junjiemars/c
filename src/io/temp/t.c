#include "_io_.h"

/*
 * 1. tmpname in stdio.h had been deprecated.
 *
 */


int
main(int argc, char **argv)
{
  int   rc;
  int   fd;
  char  tmp[NAME_MAX];
  char  buf[NAME_MAX];

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  snprintf(tmp, NAME_MAX, "%s/nore-XXXXXX", argv[1]);

  fd = mkstemp(tmp);
  if (fd == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  printf("open %s for write ...\n", tmp);

  strncpy(buf, "one line to output", NAME_MAX);

  rc = write(fd, buf, strlen(buf));
  if (rc == -1)
    {
      perror("!panic");
      rc = EXIT_FAILURE;
      goto clean_exit;
    }

  printf("wrote %d bytes\n", rc);
  rc = EXIT_SUCCESS;

 clean_exit:
  unlink(tmp);


  exit(rc);
}
