#include <_io_.h>

/*
 * Copy with avoiding holes.
 *
 */


static char  buf[BUFSIZ];



int
main(int argc, char **argv)
{
  int  n, len, sum = 0;
  int  fd_src, fd_dst;

  if (argc < 3)
    {
      fprintf(stderr, "usage: <src> <dst>\n");
      exit(EXIT_FAILURE);
    }

  fd_src = open(argv[1], O_RDONLY);
  if (fd_src == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  fd_dst = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd_dst == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  while ((n = read(fd_src, buf, BUFSIZ)) > 0)
    {
      int hole = 0;

      for (int i = 0; i < n; i++)
        {
          if (buf[i] == 0)
            {
              if (i > hole)
                {
                  len = i - hole;
                  if (write(fd_dst, buf+hole, len) != len)
                    {
                      perror(NULL);
                      exit(EXIT_FAILURE);
                    }
                  sum += len;
                  hole = i + 1;
                }
              else
                {
                  hole++;
                }
            }
        }

      if (hole < n)
        {
          len = n - hole - 1;
          if (write(fd_dst, buf+hole, len) != len)
            {
              perror(NULL);
              exit(EXIT_FAILURE);
            }
          sum += len;
        }
    }

  printf("%d bytes copied.\n", sum);


  exit(EXIT_SUCCESS);
}
