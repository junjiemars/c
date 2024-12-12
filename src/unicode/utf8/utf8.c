#include "../_unicode_.h"
#include <locale.h>
#include <stdio.h>

#define TO_BASE_N (sizeof (unsigned) * 8 + 1)
#define TO_BASE(n, b) to_base ((unsigned char[TO_BASE_N]){ "" }, (n), (b))
#define OUT_SIZE(t)                                                           \
  do                                                                          \
    {                                                                         \
      printf ("sizeof(%s) \t= %zu bytes\n", #t, sizeof (t));                  \
    }                                                                         \
  while (0)

#if MSVC
#pragma warning(disable : 4244)
#endif

const unsigned char *
to_base (unsigned char *o, unsigned i, unsigned base)
{
  unsigned char *s = &o[TO_BASE_N - 1];
  *s = 0;
  do
    {
      s--;
      *s = "0123456789ABCDEF"[i % base];
      i /= base;
    }
  while (i);

  return s;
}

void
out (const char *s, unsigned c)
{
  if (c < 0x0080)
    {
      unsigned char o[1 + 1] = { 0 };
      *o = c;
      printf ("%s: 0x%08x %32s \t%s\n", s, c, TO_BASE (c, 2), o);
    }
  else if (c < 0x0800)
    {
      unsigned char o[2 + 1] = { 0 };
      unsigned u2;
      o[0] = u2 = 0xc0 | ((c >> 6) & 0x1f);
      o[1] = u2 = (u2 << 8) | (0x80 | (c & 0x3f));
      printf ("%s: 0x%08x %32s \t%s\n", s, c, TO_BASE (u2, 2), o);
    }
  else if (c < 0x10000)
    {
      unsigned char o[3 + 1] = { 0 };
      unsigned u3;
      o[0] = u3 = 0xe0 | ((c >> 12) & 0x0f);
      o[1] = u3 = (u3 << 8) | (0x80 | ((c >> 6) & 0x3f));
      o[2] = u3 = (u3 << 8) | (0x80 | ((c & 0x3f)));
      printf ("%s: 0x%08x %32s \t%s\n", s, c, TO_BASE (u3, 2), o);
    }
  else if (c < 0x200000)
    {
      unsigned char o[4 + 1] = { 0 };
      unsigned u4;
      o[0] = u4 = 0xf0 | ((c >> 18) & 0x07);
      o[1] = u4 = (u4 << 8) | (0x80 | ((c >> 12) & 0x3f));
      o[2] = u4 = (u4 << 8) | (0x80 | ((c >> 6) & 0x3f));
      o[3] = u4 = (u4 << 8) | (0x80 | (c & 0x3f));
      printf ("%s: 0x%08x %32s \t%s\n", s, c, TO_BASE (u4, 2), o);
    }
}

int
main (void)
{
  OUT_SIZE (unsigned);
  OUT_SIZE (unsigned char);
  out ("$", 0x0024u);
  out ("¢", 0x00a2u);
  out ("€", 0x20acu);
  out ("¥", 0x00a5);

  return 0;
}
