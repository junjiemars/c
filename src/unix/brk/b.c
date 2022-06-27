#include <_unix_.h>
#include <stdio.h>

static void test_brk(void);
static void test_sbrk(void);


int
main(int argc, char **argv)
{
  _unused_(argc);
  _unused_(argv);

  test_brk();
  test_sbrk();

  return 0;
}


void
test_brk(void)
{
  int    rc;

  rc = brk(NULL);
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
