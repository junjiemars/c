#include "_cio_.h"

/*
 * fgetpos and fsetpos introduced by ISO C.
 *
 */

int
main(int argc, char **argv)
{
  char    *ss  =  "abcdefghij";
  char    *us  =  "ABC";
  size_t   len, n;
  fpos_t   pos;
  FILE    *fp;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <filename>\n");
      return 1;
    }

  fp = fopen(argv[1], "w");
  if (!fp)
    {
      perror("!panic");
      return 1;
    }

  printf("write %s into %s\n", ss, argv[1]);

  len = strlen(ss);
  if ((n = fwrite(ss, sizeof(*ss), len, fp)) != len)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  if (fgetpos(fp, &pos) == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  printf("position at %lld\n", pos);

  pos = 3;
  if (fsetpos(fp, &pos) == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }
  printf("position reset to %lld\n", pos);

  len = strlen(us);
  if ((n = fwrite(us, sizeof(*us), len, fp)) != len)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }


  exit(EXIT_SUCCESS);

}
