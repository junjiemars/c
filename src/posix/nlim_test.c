#include <nlim.h>
#include <ndef.h>
#include <stdio.h>
#include <errno.h>


#if !(MSVC)
static void pr_sysconf(const char*, int);
static void conf_line_max(void);
#endif  /* !MSVC */


int
main(void)
{

#if defined(_POSIX_VERSION)
  printf("%s: %ld\n", _str_(_POSIX_VERSION), _POSIX_VERSION+0);
#else
  printf("%s: (no symbol)\n", _str_(_POSIX_VERSION));

#endif  /* _POSIX_VERSION */

#if defined(_XOPEN_VERSION)
  printf("%s: %d\n", _str_(_XOPEN_VERSION), _XOPEN_VERSION+0);
#else
  printf("%s: (no symbol)\n", _str_(_XOPEN_VERSION));

#endif  /* _XOPEN_VERSION */


#if !(MSVC)
  conf_line_max();
#endif  /* !MSVC */


  return 0;
}


#if !(MSVC)

void
pr_sysconf(const char *ss, int name)
{
  long  rc;

  errno = 0;
  if ((rc = sysconf(name)) < 0)
    {
      if (errno != 0)
        {
          if (errno == EINVAL)
            {
              printf("%s: (not supported)\n", ss);
            }
          else
            {
              printf("%s: (sysconf error)\n", ss);
            }
        }
      else
        {
          printf("%s: (no limit)\n", ss);
        }
    }
  else
    {
      printf("%s: %ld\n", ss, rc);
    }

}


void
conf_line_max(void)
{
#if defined(LINE_MAX)
  printf("%s (defined): %ld\n", _str_(LINE_MAX), (long) (LINE_MAX+0));
#else
  printf("%s: (no symbol)\n", _str_(LINE_MAX));

#endif

#if defined(_SC_LINE_MAX)
  pr_sysconf(_str_(LINE_MAX) " (sysconf)", _SC_LINE_MAX);
#else
  printf("%s: (no symbol)\n", _str_(_SC_LINE_MAX));

#endif

#if defined(NM_LINE_MAX)
  printf("%s: %ld\n", _str_(NM_LINE_MAX), (long) (NM_LINE_MAX+0));
#else
  printf("%s: (no symbol)\n", _str_(NM_LINE_MAX);

#endif
}

#endif  /*  !MSVC */
