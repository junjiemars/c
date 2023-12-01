#include "_ctl_.h"

#include <str.h>

static void test_c_str (void);
static void test_resize (void);
static void test_shrink_to_fit (void);

static void test_copy (void);
static void test_clear (void);

static void test_iter (void);
static void test_substr (void);

int
main (void)
{
  test_c_str ();
  test_resize ();
  test_shrink_to_fit ();
  test_copy ();
  test_clear ();
  test_iter ();
  test_substr ();
}

void
test_c_str (void)
{
  str s1;
  char *c1 = "abc";

  s1 = str_init (c1);

  assert (s1.capacity > 0);
  assert (strcmp (str_c_str (&s1), c1) == 0);

  str_free (&s1);
}

void
test_resize (void)
{
  str s1;
  char *c1 = "abcdefghijklmnopqrstuvwxyz";
  size_t c1_size = strlen (c1);

  s1 = str_init (c1);
  assert (s1.size == c1_size);

  str_resize (&s1, c1_size / 2, '\0');
  assert (s1.size == c1_size / 2);

  str_resize (&s1, c1_size * 2, '\0');
  assert (s1.size == c1_size * 2);

  str_free (&s1);
}

void
test_shrink_to_fit (void)
{
  str s1;
  char *c1 = "abcdefghijklmnopqrstuvwxyz";
  size_t c1_size = strlen (c1);

  s1 = str_init (c1);
  str_resize (&s1, c1_size / 2, 0);

  assert (s1.capacity != s1.size);

  str_shrink_to_fit (&s1);
  assert (s1.capacity == s1.size);

  str_free (&s1);
}

void
test_copy (void)
{
  str s1, s2;
  char *c1 = "abcdefghijklmnopqrstuvwxyz";

  s1 = str_init (c1);
  s2 = str_copy (&s1);

  assert (str_compare (&s1, c1) == 0);
  assert (str_key_compare (&s1, &s2) == 0);

  str_free (&s1);
  str_free (&s2);
}

void
test_clear (void)
{
  str s1;
  char *c1 = "abcdefghijklmnopqrstuvwxyz";

  s1 = str_init (c1);

  str_clear (&s1);

  assert (s1.size == 0);

  str_free (&s1);
}

void
test_iter (void)
{
  str s1;
  char *c1 = "abcdefghijklmnopqrstuvwxyz";

  s1 = str_init (c1);

  for (str_it it = str_it_each (&s1); !it.done; it.step (&it))
    {
      putchar (*it.ref);
    }
  putchar ('\n');

  for (char *p = str_begin (&s1); p != str_end (&s1); p++)
    {
      putchar (*p);
    }
  putchar ('\n');

  for (size_t i = 0; i < s1.size; i++)
    {
      putchar (*str_at (&s1, i));
    }
  putchar ('\n');

  str_free (&s1);
}

void
test_substr (void)
{
  str s1, s2;
  char *c1 = "abcdefghijklmnopqrstuvwxyz";

  s1 = str_init (c1);
  s2 = str_substr (&s1, 0, 3);

  assert (str_compare (&s2, "abc") == 0);

  str_free (&s1);
  str_free (&s2);
}
