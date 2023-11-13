#include "_process_.h"

/*
 * 1. Since POSIX.1-2001, `brk' is not a part of POSIX standard
 * anymore.
 *
 * 2. Bearing in mind: the `malloc' will call `brk' twice, think about
 * it why. Change `ALLOC_SIZE' then trace `malloc' call and see whats
 * happens.
 *
 */

#define ALLOC_SIZE sizeof (long long)

static void test_brk (void);
static void test_sbrk (void);
static void test_alloc (void);

static int ds_var = 0x1122;
static int bss_var;

int
main (void)
{
  test_brk ();
  test_sbrk ();
  test_alloc ();

  return 0;
}

void
test_brk (void)
{
  if (brk (0) == -1)
    {
      perror (NULL);
      return;
    }
}

void
test_sbrk (void)
{
  void *rp;
  if ((rp = sbrk (0)) == (void *)-1)
    {
      perror (NULL);
      return;
    }
}

void
test_alloc (void)
{
  int sn = 0;
  char *ss, *ss1;
  intptr_t *bp1, *bp2, *bp3;

  if ((bp1 = sbrk (0)) == (void *)-1)
    {
      perror (NULL);
      return;
    }
  if ((brk ((char *)bp1 + ALLOC_SIZE)) == -1)
    {
      perror (NULL);
      return;
    }
  bp2 = sbrk (0);
  if (bp2 == (void *)-1)
    {
      perror (NULL);
      return;
    }
  assert ((char *) bp2 == (char *)bp1 + ALLOC_SIZE);

  bp3 = sbrk (ALLOC_SIZE);
  if (bp3 == (void *)-1)
    {
      perror (NULL);
      return;
    }
  assert (bp2 == bp3);

  bp3 = sbrk (0);
  if (bp3 == (void *)-1)
    {
      perror (NULL);
      return;
    }

  ss1 = malloc (ALLOC_SIZE);
  if (!ss1)
    {
      perror (NULL);
      return;
    }

  ss = (char *)bp1;
  printf ("%2d %p (___) %-8s\n", ++sn, bp1, ss);

  ss = (char *)bp2;
  printf ("%2d %p (sbrk) %-8s\n", ++sn, bp2, ss);

  ss = (char *)bp3;
  printf ("%2d %p (sbrk) %-8s\n", ++sn, bp3, ss);

  ss = (char *)ss1;
  printf ("%2d %p (malloc) %-8s\n", ++sn, ss1, ss1);

  printf ("%2d %p (bss) %#-8x\n", ++sn, &bss_var, bss_var);
  printf ("%2d %p (ds) %#-8x\n", ++sn, &ds_var, ds_var);
}
