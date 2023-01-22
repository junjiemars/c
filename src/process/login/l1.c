#include "_process_.h"
#include <pwd.h>
#include <grp.h>



int
main(int argc, char *argv[])
{
  char           *login     =  NULL;
  char           *code      =  NULL;
  char           *ciphered  =  NULL;
  struct passwd  *passwd    =  NULL;

  if (argc < 2)
    {
      fprintf(stderr, "usage: <login>\n");
    }
  login = argv[1];

  errno = 0;
  if ((passwd = getpwnam(login)) == NULL)
    {
      if (errno)
        {
          perror(NULL);
        }
      exit(EXIT_FAILURE);
    }

  code = getpass("X> ");

  ciphered = crypt(code, "_0002abcd");
  (void) ciphered;

  /* compare passwod */

  /* login correctly */


  /* chdir(passwd->pw_dir); */

  /* chown("/what/terminal", passwd->pw_uid, passwd->pw_gid); */

  /* chmod("/what/terminal", 0666); */

  /* setgid(passwd->pw_gid); */

  /* initgroups(passwd->pw_name, passwd->pw_gid); */

  /* execl(passwd->pw_shell, "-l", 0); */


  exit(EXIT_SUCCESS);
}
