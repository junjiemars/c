#include <_io_.h>


/*
 * stat file type.
 *
 */

static const char  *file_type(mode_t);


int
main(int argc, char *argv[])
{
  int           rc;
  struct stat   ss;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <pathname...>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      rc = lstat(argv[i], &ss);
      if (rc == -1)
        {
          perror(argv[i]);
          continue;
        }

      printf("%s: %s\n", argv[i], file_type(ss.st_mode));

    }

  exit(EXIT_SUCCESS);
}


const char *
file_type(mode_t m)
{
  if (S_ISREG(m))
    {
      return "regular";
    }
  else if (S_ISDIR(m))
    {
      return "directory";
    }
  else if (S_ISCHR(m))
    {
      return "character special";
    }
  else if (S_ISBLK(m))
    {
      return "block special";
    }
  else if (S_ISFIFO(m))
    {
      return "fifo";
    }
  else if (S_ISLNK(m))
    {
      return "symbolic link";
    }
  else if (S_ISSOCK(m))
    {
      return "socket";
    }
  else
    {
      return "(unknown file type)";
    }
}
