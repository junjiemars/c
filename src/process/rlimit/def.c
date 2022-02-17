#include "_process_.h"
#include <stdio.h>
#include <sys/resource.h>


#define out_rlim(name) print_rlimit(#name, name)


static void print_rlimit(const char *name, int resource);

static void
print_rlimit(const char *name, int resource)
{
  struct rlimit r;

  getrlimit(resource, &r);

  printf("%-18s cur=0x%016zx, max=0x%016zx\n", name, r.rlim_cur, r.rlim_max);
}


int
main(void)
{
#if defined(RLIMIT_AS)
  out_rlim(RLIMIT_AS);
#endif

#if defined(RLIMIT_CORE)
  out_rlim(RLIMIT_CORE);
#endif

#if defined(RLIMIT_CPU)
  out_rlim(RLIMIT_CPU);
#endif

#if defined(RLIMIT_DATA)
  out_rlim(RLIMIT_DATA);
#endif

#if defined(RLIMIT_FSIZE)
  out_rlim(RLIMIT_FSIZE);
#endif

#if defined(RLIMIT_MEMLOCK)
  out_rlim(RLIMIT_MEMLOCK);
#endif

#if defined(RLIMIT_NOFILE)
  out_rlim(RLIMIT_NOFILE);
#endif

#if defined(RLIMIT_NPROC)
  out_rlim(RLIMIT_NPROC);
#endif

#if defined(RLIMIT_RSS)
  out_rlim(RLIMIT_RSS);
#endif

#if defined(RLIMIT_STACK)
  out_rlim(RLIMIT_STACK);
#endif

}
