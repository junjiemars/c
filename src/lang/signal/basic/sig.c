#include <_lang_.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

#ifdef MSVC
static void psignal(int sig, const char *s);
#else
#include <unistd.h>
#endif

#define N_CNT 8

typedef void (*on_signal)(int);

static volatile int s_flag = 0;

static void on_sigint_stop(int sig);
static void on_sigint_continue(int sig);
/* static void on_sigkill_continue(int sig); */

#ifdef MSVC
#  pragma warning(disable: 4996)
#  include <windows.h>
#  include <process.h>
#  define sleep(x) Sleep((x) * 1000)
#  define getpid() _getpid()
void
psignal(int sig, const char *s)
{
	static char *tbl[] =
    {
      "default",
      0,
      "interrupt",           /* SIGINT */
      0,
      "illegal instruction", /* SIGILL */
      0,
    };

	char *msg = (sig < 0 || sig >= sizeof(tbl)/sizeof(*tbl))
		? "unknown signal" : tbl[sig];

	if (0 == s || '\0' == s[0])
    {
      fprintf(stderr, "%s\n", msg);
    }
  else
    {
      fprintf(stderr, "%s: %s\n", s, msg);
    }
}
#endif  /* end of MSVC */

void
on_sigint_stop(int sig)
{
	psignal(sig, "^ on_sigint_stop");
	s_flag = sig;
}

void
on_sigint_continue(int sig)
{
	psignal(sig, "^ on_sigint_continue");
	/* continue put into pending signals */
	signal(sig, on_sigint_stop);
}

void
on_sigkill_continue(int sig)
{
  psignal(sig, "^ on_sigkill_continue");
  signal(sig, on_sigint_stop);
}

int
main(int argc, char **argv)
{
	_unused_(argc);
	_unused_(argv);

	printf("pid=%d\n", getpid());
	
	int n = 0;
	on_signal onsig = signal(SIGINT, on_sigint_continue);
  if (SIG_ERR == onsig)
    {
      perror("!panic, signal");
      return 1;
    }

	do
    {
      if (s_flag)
        {
          fprintf(stderr, "stop, s_flag = %i\n", s_flag);
          break;
        }
      if (3 == n)
        {
          int rc = raise(SIGINT);
          if (rc)
            {
              perror("!panic, raise SIGINT");
            }
        }
      else
        {
          fprintf(stderr, "sleeping 1s (%i/%i)...\n", n+1, N_CNT);
        }
      sleep(1);
    } while (++n < N_CNT);

	return 0;
}
