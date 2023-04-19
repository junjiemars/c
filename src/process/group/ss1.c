#include "_process_.h"

#define print_ids(h, s, p, g, pp)                                       \
  do                                                                    \
    {                                                                   \
      printf("%s: sid=%d, pid=%d, pgid=%d, ppid=%d\n", h, s, p, g, pp); \
    } while (0)


int
main(void)
{
  pid_t  sid, pid, pgid, ppid;

  pid = getpid();
  pgid = getpgid(0);
  ppid = getppid();
  sid = getsid(0);

  print_ids(">", sid, pid, pgid, ppid);

  if ((sid = setsid()) == -1)
    {
      perror("pid == pgid");
      assert(pid == pgid);
    }
  else
    {
      sid = getsid(0);
      pgid = getpgid(0);
      print_ids("setsid()", sid, pid, pgid, ppid);
    }

  if ((pid = fork()) == -1)
    {
      perror(NULL);
    }
  else if (pid == 0)
    {
      pid_t  cid  =  getpid();
      sid = getsid(0);
      pgid = getpgid(0);
      ppid = getppid();

      print_ids(">", sid, cid, pgid, ppid);

      if ((sid = setsid()) == -1)
        {
          perror("setsid() in child");
        }
      else
        {
          sid = getsid(0);
          pgid = getpgid(0);
          print_ids("setsid()", sid, cid, pgid, ppid);
        }
      exit(0);
    }

  if (waitpid(pid, 0, 0) < 0)
    {
      perror(NULL);
      exit(1);
    }

  exit(0);
}
