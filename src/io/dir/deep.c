#include <_io_.h>

#define DEPTH      100
#define PATHSIZ    (PATH_MAX * DEPTH)
#define BEGIN_DIR  "xxxxxxxxxx"
#define DIR_NAME   "alonglonglonglonglonglonglonglonglonglongname"
#define FILE_NAME  "yyyyyyyyyy"

int
main(int argc, char **argv)
{
  char    *path;
  size_t   size;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <dir>\n");
      exit(EXIT_FAILURE);
    }

  if (chdir(argv[1]) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  if (faccessat(AT_FDCWD, BEGIN_DIR, F_OK, 0) == 0)
    {
      if (unlinkat(AT_FDCWD, BEGIN_DIR, AT_REMOVEDIR) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  if (mkdir(BEGIN_DIR, 0755) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  if (chdir(BEGIN_DIR) == -1)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }


  for (int i = 0; i < DEPTH; i++)
    {
      if (mkdir(DIR_NAME, 0755) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }

      if (chdir(DIR_NAME) == -1)
        {
          perror(NULL);
          exit(EXIT_FAILURE);
        }
    }

  size = PATH_MAX;
  if ((path = malloc(PATH_MAX)) == NULL)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }

  for (;;)
    {
      if (getcwd(path, size) != NULL)
        {
          break;
        }
      else
        {
          perror("getcwd");
          size *= 2;
          if (size > PATHSIZ)
            {
              fprintf(stderr, "!%zu exceed %zu: %s\n",
                      size, (size_t) PATHSIZ, strerror(errno));
              exit(EXIT_FAILURE);
            }

          if ((path = realloc(path, size)) == NULL)
            {
              perror(NULL);
              exit(EXIT_FAILURE);
            }
        }
    }

  printf("length = %zu\n%s\n", strlen(path), path);


  exit(EXIT_SUCCESS);
}
