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
  char *ss;
  intptr_t *bp1, *bp2, *bp3, *bp4, *bp5;

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

  ss = malloc (ALLOC_SIZE);
  if (!ss)
    {
      perror (NULL);
      return;
    }
  bp4 = sbrk (0);
  if (bp4 == (void *)-1)
    {
      perror (NULL);
      return;
    }

  free (ss);
  bp5 = sbrk (0);
  if (bp5 == (void *)-1)
    {
      perror (NULL);
      return;
    }

  printf ("%2d %p ___\n", ++sn, bp1);
  printf ("%2d %p bss\n", ++sn, &bss_var);
  printf ("%2d %p ds\n", ++sn, &ds_var);
  printf ("%2d %p sbrk\n", ++sn, bp2);
  printf ("%2d %p sbrk\n", ++sn, bp3);
  printf ("%2d %p malloc\n", ++sn, bp4);
  printf ("%2d %p free\n", ++sn, bp5);
}
