#include "_data_.h"
#include <pwd.h>

/*
 * getpwuid1 is an emulation of `getpwuid'.
 *
 */

extern void  print_passwd(const struct passwd*);

static struct passwd  *getpwuid1(uid_t);


int
main(int argc, char **argv)
{
  if (argc < 2)
    {
      fprintf(stderr, "usage: <login...>\n");
      exit(EXIT_FAILURE);
    }

  for (int i = 1; i < argc; i++)
    {
      struct passwd  *pwd;

      errno = 0;
      if ((pwd = getpwuid1((uid_t) atoi(argv[i]))) == NULL)
        {
          if (errno)
            {
              perror(NULL);
            }

          continue;
        }

      print_passwd(pwd);
    }

  exit(EXIT_SUCCESS);
}


struct passwd *
getpwuid1(uid_t uid)
{
  struct passwd  *p;

  setpwent();

  while ((p = getpwent()) != NULL)
    {
      if (uid == p->pw_uid)
        {
          break;
        }
    }

  endpwent();

  return p;
}
