#include <_lang_.h>



size_t
self_strlen(const char *s)
{
  size_t len = 0;
  while (*s++)
    {
      len++;
    }
  return len;
}

int
self_strcmp(const char *s1, const char *s2)
{
  while (*s1 && (*s1 == *s2))
    {
      s1++, s2++;
    }
  return *(const unsigned char*) s1 - *(const unsigned char*) s2;
}

char *
self_strcpy(char *dst, const char *src)
{
  char *r = dst;
  while (0 != (*dst++ = *src++));
  return r;
}

char *
self_strcat(char *s1, const char *s2)
{
  size_t len = strlen(s1);
  return strcpy(s1 + len, s2);
}

void
test_empty(void)
{
  char  *s  =  "";
  char a[]  =  "";
  assert(0 == strlen(s));
  assert(0 == strlen(a));

#if NDEBUG
  _unused_(s);
  _unused_(a);
#endif
}

void
test_static_len(void)
{
  assert((sizeof("abc") - 1) == strlen("abc"));
}

void
test_strlen(char *s)
{
  size_t len1 = strlen(s);
  size_t len2 = self_strlen(s);

  assert((len1 == len2) && "self_strlen() failed");
#if NDEBUG
  _unused_(len1);
  _unused_(len2);
#endif
}

void
test_strcpy(void)
{
  char  buf1[8], buf2[8];
  int   len  =  sizeof(buf1)/sizeof(*buf1);

  memset(buf1, 0x11, len);
  assert(0x11 == buf1[len-1] && "strcpy(), 0x11 != <tailing>");

  strcpy(buf1, "");
  assert(0 == strlen(buf1) && "strcpy(), copy empty string failed");

  strcpy(buf1, "abc");
  assert(0 == buf1[strlen(buf1)] && "strcpy(), 0 != <tailing>");
  assert(0x11 == buf1[len-1] && "strcpy(), 0x11 != <tailing>");

  self_strcpy(buf2, "abc");
  assert(0 == strncmp(buf1, buf2, len) && "self_strcpy(), 0 != <tailing>");
}

void
test_strcmp(char *s)
{
  size_t   len  =  strlen(s);
  char    *d1   =  malloc(len+1);
  char    *d2   =  strcpy(d1, s);
  char     buf[8];

  assert(d1 == d2 && "strcpy(), diff between dest and retval");
  assert(0 == strcmp(s, d1)
         && 0 == self_strcmp(s, d1)
         && 0 == self_strcmp(d1, s)
         && "self_strcpy(), failed");


  d2 = buf;
  strcpy(d1, "abc");
  strcpy(d2, "abx");
  assert(0 != strcmp(d1, d2)
         && 0 != self_strcmp(d1, d2)
         && "self_strcmp(), 0 !=");
  assert(0 > strcmp(d1, d2)
         && 0 > self_strcmp(d1, d2)
         && 0 < self_strcmp(d2, d1)
         && "self_strcmp(), 0 ><");
  free(d1);
}

void
test_strcat(void)
{
  char  buf1[8];
  _unused_(char  buf2[8]);

  memset(buf1, 0, sizeof(buf1)/sizeof(*buf1));
  memset(buf2, 0, sizeof(buf2)/sizeof(*buf2));

  strcat(&buf1[0], "abc");
  assert(0 == strcmp(buf1, "abc") && "strcat(), failed");

  self_strcat(buf2, "abc");
  assert(0 == strcmp(buf2, buf1) && "self_strcat(), failed");

  self_strcat(buf2, "");
  assert(0 == strcmp(buf2, buf1) && "self_strcat(), failed");

  self_strcat(buf2, "x");
  assert(0 == strcmp(buf2, "abcx") && "self_strcat(), failed");
}

int
main(_unused_(int argc), char **argv)
{
  test_empty();
  test_static_len();
  test_strlen(argv[0]);
  test_strcpy();
  test_strcmp(argv[0]);
  test_strcat();

  return 0;
}
