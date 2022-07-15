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
  char     buf[NM_LINE_MAX];
  size_t   len, n;
  fpos_t   pos;
  FILE    *fp;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <filename>\n");
      exit(EXIT_FAILURE);
    }

  fp = fopen(argv[1], "w+");
  if (!fp)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  printf("write \"%s\" into %s\n", ss, argv[1]);

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

  printf("position at %ld\n", _fpos_(pos));

  _fpos_(pos) = 3;
  if (fsetpos(fp, &pos) == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }
  printf("position reset to %ld\n", _fpos_(pos));

  len = strlen(us);
  if ((n = fwrite(us, sizeof(*us), len, fp)) != len)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }

  if (fflush(fp))
    {
      perror("!panic");
      clearerr(fp);
    }

  _fpos_(pos) = 0;
  if (fsetpos(fp, &pos) == -1)
    {
      perror("!panic");
      exit(EXIT_FAILURE);
    }
  printf("position reset to %ld\n", _fpos_(pos));

  if ((n = fread(buf, sizeof(*buf), NM_LINE_MAX, fp)) == 0)
    {
      if (ferror(fp))
        {
          perror("!panic");
          exit(EXIT_FAILURE);
        }
    }
  printf("read \"%s\" from %s\n", buf, argv[1]);


  exit(EXIT_SUCCESS);

}
