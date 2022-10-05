#include <_io_.h>
#include <dirent.h>


int
main(int argc, char **argv)
{
  DIR            *dir;
  struct dirent  *ent;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <dir>\n");
      exit(EXIT_FAILURE);
    }

  dir = opendir(argv[1]);
  if (dir == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  while ((ent = readdir(dir)) != NULL)
    {
      long loc = telldir(dir);
      printf("#%07ld: %s\n", loc, ent->d_name);
    }

  closedir(dir);


  exit(EXIT_SUCCESS);
}
