#include "_stdio_.h"


/*
 * 1. fgetpos and fsetpos introduced by ISO C.
 * 2. https://pubs.opengroup.org/onlinepubs/9699919799/functions/fgetpos.html
 *
 */

int
main(int argc, char **argv)
{
  char    *ss  =  "abcdefghij";
  char    *us  =  "ABC";
  char     buf[BUFSIZ];
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
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  printf("write \"%s\" into %s\n", ss, argv[1]);

  len = strlen(ss);
  if ((n = fwrite(ss, sizeof(*ss), len, fp)) != len)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (fgetpos(fp, &pos) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("position at %lld\n", (long long) _fpos_(pos));

  _fpos_(pos) = 3;
  if (fsetpos(fp, &pos) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("position reset to %lld\n", (long long) _fpos_(pos));

  len = strlen(us);
  if ((n = fwrite(us, sizeof(*us), len, fp)) != len)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (fflush(fp))
    {
      perror(NULL);
      clearerr(fp);
    }

  _fpos_(pos) = 0;
  if (fsetpos(fp, &pos) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  printf("position reset to %lld\n", (long long) _fpos_(pos));

  if ((n = fread(buf, sizeof(*buf), BUFSIZ, fp)) == 0)
    {
      if (ferror(fp))
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }
  printf("read \"%s\" from %s\n", buf, argv[1]);


  exit(EXIT_SUCCESS);

}
