#include <_lang_.h>
#include <setjmp.h>

/*
 * 1. configure --has-lang --with-optimize=no
 *
 * 2. configure --has-lang --with-optimize=yes
 *
 */


static void f1(int, int, int, int);
static void f2(int);
static void print_var(int, int, int, int);

static jmp_buf  jmpenv;
static int      g_var;

int
main(void)
{
  auto int      a_var;
  register int  r_var;
  static int    s_var;
  volatile int  v_var;

  if (setjmp(jmpenv) != 0)
    {
      printf("%s (longjmp)\n------------\n", __FUNCTION__);
      print_var(a_var, r_var, s_var, v_var);
      return 0;
    }

  g_var = 1, a_var = 2, r_var = 3,  s_var = 4, v_var = 5;

  printf("%s (setjmp)\n------------\n", __FUNCTION__);
  print_var(a_var, r_var, s_var, v_var);

  g_var = 11, a_var = 12, r_var = 13, s_var = 14, v_var = 15;

  f1(a_var, r_var, s_var, v_var);

  return 0;
}

void
print_var(int a1, int r1, int s1, int v1)
{
  printf("global=%02d,auto=%02d,register=%02d,static=%02d,volatile=%02d\n",
         g_var, a1, r1, s1, v1);
}

void
f1(int a1, int r1, int s1, int v1)
{
  printf("%s\n------------\n", __FUNCTION__);
  print_var(a1, r1, s1, v1);

  f2(1);
}

void
f2(int rc)
{
  longjmp(jmpenv, rc);
}
