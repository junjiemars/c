#include "_process_.h"
#include <stdio.h>
#include <stdlib.h>

#define ALLOC_SIZE  sizeof(long)


static void test_brk(void);
static void test_sbrk(void);
static void test_alloc(void);

static int  ds_var  =  0x1122;
static int  bss_var;


int
main(void)
{
  test_brk();
  test_sbrk();
  test_alloc();

  return 0;
}


void
test_brk(void)
{
  int    rc;

  rc = brk(0);
  if (rc)
    {
      perror(NULL);
      return;
    }

}

void
test_sbrk(void)
{
  void  *rp;

  rp = sbrk(0);
  if (rp == (void *) -1)
    {
      perror(NULL);
      return;
    }

}

void
test_alloc(void)
{
  int        rc;
  char      *ss, *ss1;
  intptr_t  *rp;

  rp = sbrk(0);
  if (rp == (void *) -1)
    {
      perror(NULL);
      return;
    }

  rc = brk(rp + ALLOC_SIZE);
  if (rc == -1)
    {
      perror(NULL);
      return;
    }

  rp = sbrk(0);
  if (rp == (void *) -1)
    {
      perror(NULL);
      return;
    }

  ss1 = malloc(ALLOC_SIZE);
  if (!ss1)
    {
      perror(NULL);
      return;
    }

  ss = (char *) rp;
  snprintf(ss, ALLOC_SIZE, "%s", "ABCD");
  printf("%-8s%p\n", ss, rp);

  snprintf(ss1, ALLOC_SIZE, "%s", "abcd");
  printf("%-8s%p\n", ss1, ss1);

  printf("%#-8x%p\n", bss_var, &bss_var);
  printf("%#-8x%p\n", ds_var, &ds_var);

}
