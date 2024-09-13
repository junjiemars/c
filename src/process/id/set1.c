#include "_process_.h"

static void print_ids (uid_t, uid_t);
static void print_err (char *, uid_t, int);

int
main (void)
{
  uid_t suid, seuid;

#if defined(_POSIX_SAVED_IDS)
  printf ("%s=%ld\n", _str_ (_POSIX_SAVED_IDS), (long)_POSIX_SAVED_IDS);
#endif

  suid = getuid ();
  seuid = geteuid ();
  print_ids (suid, seuid);

  if (setuid (seuid) < 0)
    {
      print_err (_str_ (stduid), seuid, errno);
    }
  print_ids (suid, seuid);

  if (setuid (suid) < 0)
    {
      print_err (_str_ (stduid), suid, errno);
    }
  print_ids (suid, seuid);

  if (setuid (seuid) < 0)
    {
      print_err (_str_ (setuid), seuid, errno);
    }
  print_ids (suid, seuid);

  if (seteuid (seuid) < 0)
    {
      print_err (_str_ (seteuid), seuid, errno);
    }
  print_ids (suid, seuid);

  exit (EXIT_SUCCESS);
}

void
print_ids (uid_t suid, uid_t seuid)
{
  pid_t pid;
  uid_t uid, euid;
  static int i = 1;

  pid = getpid ();
  uid = getuid ();
  euid = geteuid ();

  printf ("%1d. pid=%8d: "
          "uid=%6d, euid=%6d, saved-uid=%6d, saved-euid=%6d\n",
          i++, pid, uid, euid, suid, seuid);
}

void
print_err (char *fn, uid_t uid, int err)
{
  printf ("!%s(%d): %s\n", fn, uid, strerror (err));
}
