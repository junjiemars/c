#include "_process_.h"

int
main (int argc, char **argv)
{
  struct rlimit rl;
  int fd;
  char *fname;
  int err;

  if (argc < 2)
    {
      printf ("usage: %s <filename>\n", argv[0]);
      return 1;
    }
  fname = argv[0];

  if (getrlimit (RLIMIT_NOFILE, &rl) == -1)
    {
      perror (NULL);
      return 1;
    }
  printf ("RLIMIT_NOFILE: cur = %li\n", (long)rl.rlim_cur);

  rl.rlim_cur = 1;
  if (setrlimit (RLIMIT_NOFILE, &rl) == -1)
    {
      perror (NULL);
      return 1;
    }
  if (getrlimit (RLIMIT_NOFILE, &rl) == -1)
    {
      perror (NULL);
      return 1;
    }
  printf ("RLIMIT_NOFILE: cur = %li\n", (long)rl.rlim_cur);

  if ((fd = open (fname, O_RDONLY)) == -1)
    {
      err = errno;
      perror (NULL);
      assert (err == EMFILE);
    }

  return 0;
}
