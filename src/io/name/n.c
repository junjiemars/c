#include <_io_.h>


int
main(int argc, char **argv)
{

#if defined(NAME_MAX)
  printf("NAME_MAX=%lu\n", (unsigned long) (NAME_MAX + 0));
#else
  printf("NAME_MAX=(no symbol)\n");
#endif

#if defined(_POSIX_NAME_MAX)
  printf("_POSIX_NAME_MAX=%lu\n", (unsigned long) (_POSIX_NAME_MAX + 0));
#else
  printf("_POSIX_NAME_MAX=(no symbol)\n");
#endif

#if defined(_POSIX_NO_TRUNC)
  printf("_POSIX_NO_TRUNC=%lu\n", (unsigned long) (_POSIX_NO_TRUNC + 0));
#else
  printf("_POSIX_NO_TRUNC=(no symbol)\n");
#endif

  for (int i = 1; i < argc; i++)
    {
      printf("argv[%d]: %s\n------------\n", i, argv[i]);

#if defined(_PC_NAME_MAX)
      long name_max = pathconf(argv[i], _PC_NAME_MAX);
      if (name_max == -1)
        {
          perror(NULL);
          continue;
        }
      printf("_PC_NAME_MAX=%ld\n", name_max);

#endif

#if defined(_PC_PATH_MAX)
      long path_max = pathconf(argv[i], _PC_PATH_MAX);
      if (path_max == -1)
        {
          perror(NULL);
          continue;
        }
      printf("_PC_PATH_MAX=%ld\n", path_max);

#endif

      int fd = open(argv[1], O_RDONLY);
      if (fd == -1)
        {
          perror(NULL);
        }
    }



  exit(EXIT_SUCCESS);
}
