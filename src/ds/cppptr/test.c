#include "../_ds_.h"
#include "shared_ptr.h"
#include "unique_ptr.h"

static void test_unique_ptr (void);
static void test_shared_ptr (void);

int
main (void)
{
  test_unique_ptr ();
  test_shared_ptr ();
  return 0;
}

void
test_unique_ptr (void)
{
  UniquePtr *p1, *p2;

  p1 = new_unique_ptr (malloc (sizeof (int)), free);
  assert (unique_ptr_ref (p1, int) != NULL);

  *unique_ptr_ref (p1, int) = 0x1122;
  assert (unique_ptr_ref (p1, int)[0] == 0x1122);
  free_unique_ptr (p1);

  p2 = new_unique_ptr (malloc (sizeof (int)), free);
  assert (unique_ptr_ref (p2, int) != NULL);

  *unique_ptr_ref (p2, int) = 0x3344;
  unique_ptr_move (p1, p2);
  assert (unique_ptr_ref (p2, int) == NULL);
  assert (*unique_ptr_ref (p1, int) == 0x3344);

  free_unique_ptr (p1);
}

void
test_shared_ptr (void)
{
  SharedPtr *p1, *p2;

  p1 = new_shared_ptr (malloc (sizeof (int)), free);
  assert (p1 != NULL);
  assert (shared_ptr_count (p1) == 1);
  *shared_ptr_ref (p1, int) = 0x1122;

  p2 = shared_ptr_copy (p1);
  assert (shared_ptr_count (p2) == 2);
  assert (*shared_ptr_ref (p2, int) == 0x1122);

  shared_ptr_drop (p2);
  shared_ptr_drop (p2);
  assert (shared_ptr_count (p2) == 0);

  free_shared_ptr (p1);
}
