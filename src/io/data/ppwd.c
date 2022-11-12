#include "_io_.h"
#include <pwd.h>

void
print_passwd(const struct passwd *pwd)
{
  printf("name: %s\n"
         "passwd: %s\n"
         "uid: %li\n"
         "gid: %li\n"
         "comment: %s\n"
         "dir: %s\n"
         "shell: %s\n",
         pwd->pw_name,
         pwd->pw_passwd,
         (long) pwd->pw_uid,
         (long) pwd->pw_gid,
         pwd->pw_gecos,
         pwd->pw_dir,
         pwd->pw_shell);

}
