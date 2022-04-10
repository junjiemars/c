#include "_io_.h"
#include <sys/stat.h>


/*
 * check setuid and setgid
 *
 */


int
main(int argc, char **argv)
{
  int          rc;
  struct stat  buf;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  rc = lstat(argv[1], &buf);
  if (rc == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  printf("set-user-id is %s\n", buf.st_mode & S_ISUID ? "on" : "off");
  printf("set-group-id is %s\n", buf.st_mode & S_ISGID ? "on" : "off");


  exit(EXIT_SUCCESS);
}
