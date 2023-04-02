#include "_process_.h"


static void  print_ids(uid_t, uid_t);


int
main(void)
{
  uid_t  suid, seuid;

#if defined(_POSIX_SAVED_IDS)
  printf("%s=%ld\n", _str_(_POSIX_SAVED_IDS), (long) _POSIX_SAVED_IDS);
#endif

  suid = getuid();
  seuid = geteuid();
  print_ids(suid, seuid);

  if (setuid(seuid) < 0)
    {
      perror(_str_(seuid));
      exit(EXIT_FAILURE);
    }
  print_ids(suid, seuid);

  if (setuid(suid) < 0)
    {
      perror(_str_(suid));
      exit(EXIT_FAILURE);
    }
  print_ids(suid, seuid);

  if (setuid(seuid) < 0)
    {
      perror(_str_(seuid));
      exit(EXIT_FAILURE);
    }
  print_ids(suid, seuid);


  exit(EXIT_SUCCESS);
}


void
print_ids(uid_t suid, uid_t seuid)
{
  pid_t       pid;
  uid_t       uid, euid;
  static int  i  =  1;

  pid = getpid();
  uid = getuid();
  euid = geteuid();

  printf("No%1d. pid=%8d: "
         "uid=%6d, euid=%6d, saved-uid=%6d, saved-euid=%6d\n",
         i++, pid, uid, euid, suid, seuid);
}
