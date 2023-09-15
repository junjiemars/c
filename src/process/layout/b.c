#include "_process_.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * 1. `brk` is not a part of POSIX standard, since POSIX.1-2001.
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
  char *ss, *ss1;
  intptr_t *bp, *bp1;

  if ((bp = sbrk (0)) == (void *)-1)
    {
      perror (NULL);
      return;
    }

  if ((brk ((char *)bp + ALLOC_SIZE)) == -1)
    {
      perror (NULL);
      return;
    }

  bp1 = sbrk (0);
  if (bp1 == (void *)-1)
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

  ss = (char *)bp;
  snprintf (ss, ALLOC_SIZE, "%s", "___");
  printf ("%-8s%p\n", ss, bp);

  ss = (char *)bp1;
  snprintf (ss, ALLOC_SIZE, "%s", "ABC");
  printf ("%-8s%p (brk)\n", ss, bp1);

  snprintf (ss1, ALLOC_SIZE, "%s", "abc");
  printf ("%-8s%p (malloc)\n", ss1, ss1);

  printf ("%#-8x%p (bss)\n", bss_var, &bss_var);
  printf ("%#-8x%p (ds)\n", ds_var, &ds_var);
}
