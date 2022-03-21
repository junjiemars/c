#include "nustd.h"
#include <stdio.h>

static void test_sleep(void);
static void test_getpid(void);


int
main(void)
{
  test_sleep();
  test_getpid();

  return 0;
}


void
test_sleep(void)
{
  printf("sleep(1) ...\n");
  sleep(1);
}

void
test_getpid(void)
{
  printf("pid: %d\n", getpid());
}
