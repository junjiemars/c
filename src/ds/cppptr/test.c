#include "../_ds_.h"
#include "unique_ptr.h"

static void test_unique_ptr (void);

int
main (void)
{
  test_unique_ptr ();
  return 0;
}

void
test_unique_ptr (void)
{
  UniquePtr ptr1, ptr2;

  ptr1 = new_unique_ptr (malloc (sizeof (int)), free);
  assert (unique_ptr_ref (&ptr1, int) != NULL);
  *unique_ptr_ref (&ptr1, int) = 0x1122;
  assert (unique_ptr_ref (&ptr1, int)[0] == 0x1122);
  free_unique_ptr (&ptr1);

  ptr2 = new_unique_ptr (malloc (sizeof (int)), free);
  assert (unique_ptr_ref (&ptr2, int) != NULL);
  *unique_ptr_ref (&ptr2, int) = 0x3344;
  unique_ptr_move (&ptr1, &ptr2);
  assert (unique_ptr_ref (&ptr2, int) == NULL);
  assert (*unique_ptr_ref (&ptr1, int) == 0x3344);
  free_unique_ptr (&ptr1);
}
