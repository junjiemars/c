#include "_process_.h"


static void  print_id3(uid_t, uid_t, pid_t);


int
main(void)
{
  pid_t         pid;
  uid_t         suid, seuid;

#if defined(_POSIX_SAVED_IDS)
  printf("%s=%ld\n", _str_(_POSIX_SAVED_IDS), (long) _POSIX_SAVED_IDS);
#endif

  pid = getpid();
  suid = getuid();
  seuid = geteuid();

  print_id3(suid, seuid, pid);

  if (setuid(seuid) < 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  print_id3(suid, seuid, pid);

  if (setuid(suid) < 0)
    {
      perror(NULL);
      exit(EXIT_FAILURE);
    }
  print_id3(suid, seuid, pid);


  exit(EXIT_SUCCESS);
}


void
print_id3(uid_t suid, uid_t seuid, pid_t pid)
{
  uid_t  uid, euid;

  uid = getuid();
  euid = geteuid();

  printf("uid=%d, euid=%d, suid=%d, seuid=%d, pid=%d\n",
         uid, euid, suid, seuid, pid);
}
