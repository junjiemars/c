#include "_io_.h"
#include <dirent.h>

int
main(int argc, char **argv)
{
  DIR *d;
  struct dirent *ent;

  if (argc < 2)
    {
      fprintf(stderr, "usage: %s <directory>\n", basename(argv[0]));
      exit(EXIT_FAILURE);
    }

  d = opendir(argv[1]);
  if (d == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  while ((ent = readdir(d)) != NULL)
    {
      printf("%s\n", ent->d_name);
    }

  closedir(d);

  exit(EXIT_SUCCESS);
}
