#include <_algo_.h>

struct A
{
  int i1;
  int i2[2];
};

union B
{
  int i1;
  int i2[2];
};

union C
{
  uint32_t u32;
  uint32_t b1 : 16;
  uint32_t b2 : 16;
};

static void print_layout (int, void *, char const *);
static void test_global_layout (void);
static void test_struct_layout (void);
static void test_union_layout (void);
static void test_bitfield_layout (void);

int g_i1 = __LINE__;
struct A g_a1 = {
  .i1 = __LINE__,
  .i2 = { __LINE__, __LINE__, },
};

int
main (void)
{
  test_global_layout ();
  test_struct_layout ();
  test_union_layout ();
  test_bitfield_layout ();
  return 0;
}

void
print_layout (int line, void *addr, char const *name)
{
  printf ("%-32s %16p line %4d\n", name, addr, line);
}

void
test_global_layout (void)
{
  print_layout (g_i1, &g_i1, _str_ (&g_i1));
  print_layout (g_a1.i1, &g_a1.i1, _str_ (&g_a1.i1));
  print_layout (g_a1.i2[0], &g_a1.i2[0], _str_ (&g_a1.i2[0]));
  print_layout (g_a1.i2[1], &g_a1.i2[1], _str_ (&g_a1.i2[1]));
}

void
test_struct_layout (void)
{
  struct A sa1 = { 0 };
  struct A sa2 = { 0 };
  struct A *ha1 = NULL;
  struct A *ha2 = NULL;

  print_layout (__LINE__, &sa1, _str_ (&sa1));
  print_layout (__LINE__, &sa2, _str_ (&sa2));
  print_layout (__LINE__, &ha1, _str_ (&ha1));
  print_layout (__LINE__, &ha2, _str_ (&ha2));

  print_layout (__LINE__, &sa1.i1, _str_ (&sa1.i1));
  print_layout (__LINE__, &sa1.i2[0], _str_ (&sa1.i2[0]));
  print_layout (__LINE__, &sa1.i2[1], _str_ (&sa1.i2[1]));

  ha1 = malloc (sizeof (struct A));
  assert (ha1 != NULL);

  print_layout (__LINE__, &ha1->i1, _str_ (&ha1->i1));
  print_layout (__LINE__, &ha1->i2[0], _str_ (&ha1->i2[0]));
  print_layout (__LINE__, &ha1->i2[1], _str_ (&ha1->i2[1]));
  free (ha1);

  ha2 = malloc (sizeof (struct A));
  assert (ha2 != NULL);
  print_layout (__LINE__, &ha2->i1, _str_ (&ha2->i1));
  print_layout (__LINE__, &ha2->i2[0], _str_ (&ha2->i2[0]));
  print_layout (__LINE__, &ha2->i2[1], _str_ (&ha2->i2[1]));
  free (ha2);
}

void
test_union_layout (void)
{
  union B sb1 = { 0 };
  union B *hb1 = NULL;

  print_layout (__LINE__, &sb1, _str_ (&sb1));
  print_layout (__LINE__, &hb1, _str_ (&hb1));

  print_layout (__LINE__, &sb1.i1, _str_ (&sb1.i1));
  print_layout (__LINE__, &sb1.i2[0], _str_ (&sb1.i2[0]));
  print_layout (__LINE__, &sb1.i2[1], _str_ (&sb1.i2[1]));

  hb1 = malloc (sizeof (union B));
  assert (hb1 != NULL);
  print_layout (__LINE__, &hb1->i1, _str_ (&hb1->i1));
  print_layout (__LINE__, &hb1->i2[0], _str_ (&hb1->i2[0]));
  print_layout (__LINE__, &hb1->i2[1], _str_ (&hb1->i2[1]));
  free (hb1);
}

void
test_bitfield_layout (void)
{
  union C sc1, sc2;

  print_layout (__LINE__, &sc1, _str_ (&sc1));
  print_layout (__LINE__, &sc2, _str_ (&sc2));

  sc1.u32 = 0x11223344;
  print_layout (__LINE__, (void *)(size_t)sc1.u32,
                _str_ ((void *)(size_t)sc1.u32));

  sc2.u32 = _flip32_ (sc1.u32);
  print_layout (__LINE__, (void *)(size_t)sc2.u32,
                _str_ ((void *)(size_t)sc2.u32));
}
