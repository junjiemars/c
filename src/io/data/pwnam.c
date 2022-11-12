#include "_io_.h"
#include <pwd.h>

extern void print_passwd(const struct passwd*);

int
main(int argc, char **argv)
{
  int             err;
  struct passwd  *pwd  =  NULL;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <login...>\n");
      exit(EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      errno = 0;
      if ((pwd = getpwnam(argv[i])) == NULL)
        {
          err = errno;
          if (err)
            {
              perror(NULL);
              exit(EXIT_FAILURE);
            }

          exit(EXIT_SUCCESS);
        }

      print_passwd(pwd);
      printf("------------\n");
    }


  exit(EXIT_SUCCESS);
}
