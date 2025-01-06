#include "../_lang_.h"

/* obsolescence */

int
main (void)
{
  int rc = bcmp ("", "", 0);
  assert (rc == 0);

  rc = bcmp ("a", "", 0);
  assert (rc == 0);

  rc = bcmp ("a", "ab", 1);
  assert (rc == 0);

  rc = bcmp ("abc", "abcd", sizeof ("abc") - 1);
  assert (rc == 0);

  return 0;
}
