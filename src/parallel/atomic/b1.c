#include "_parallel_.h"
#include <stdatomic.h>

int
main (void)
{
  atomic_int x;

  atomic_init (&x, 0x1234);
  assert (x == 0x1234);

  atomic_fetch_add (&x, 1);
  assert (x == 0x1235);

  atomic_fetch_add_explicit (&x, 1, memory_order_relaxed);
  assert (x == 0x1236);

  atomic_store (&x, 1);
  atomic_load (&x);
  assert (x == 1);

  return 0;
}
