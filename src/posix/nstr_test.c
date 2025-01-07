#include "ndef.h"
#include "nstr.h"
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#if (MSVC)
#pragma warning(disable : 4996)
#endif

static void test_strdup (void);
static void test_strerror_r (void);
static void test_strtok_r (void);

int
main (void)
{
  test_strdup ();
  test_strerror_r ();
  test_strtok_r ();

  return 0;
}

void
test_strdup (void)
{
#if !(NM_HAVE_STRDUP)
  printf ("%s: no `strdup' found\n", __FUNCTION__);

#else
  const char *s1 = "abc";
  char *s2;

  s2 = strdup (s1);
  assert (strcmp (s1, s2) == 0);

  free (s2);
#endif /* strdup */
}

void
test_strerror_r (void)
{
#if !(NM_HAVE_STRERROR_R)
  printf ("%s: no `strerror_r' found\n", __FUNCTION__);

#else
  char buf[BUFSIZ] = { 0 };
  if (strerror_r (EPERM, buf, BUFSIZ))
    {
      perror (NULL);
    }
  else
    {
      printf ("%s = %s\n", _str_ (EPERM), buf);
    }

#endif
}

void
test_strtok_r (void)
{
#if !(NM_HAVE_STRTOK_R)
  printf ("%s: no `strtok_r' found\n", __FUNCTION__);
#else
  char test[80], blah[80];
  char *sep = "\\/:;=-";
  char *word, *phrase, *brkt, *brkb;

  strcpy (test, "This;is.a:test:of=the/string\\tokenizer-function.");

  for (word = strtok_r (test, sep, &brkt); word;
       word = strtok_r (NULL, sep, &brkt))
    {
      strcpy (blah, "blah:blat:blab:blag");

      for (phrase = strtok_r (blah, sep, &brkb); phrase;
           phrase = strtok_r (NULL, sep, &brkb))
        {
          /* This:blah */
          /* This:blat */
          /* This:blab */
          /* This:blag */
          /* ... */
          /* function.:blah */
          /* function.:blat */
          /* function.:blab */
          /* function.:blag */
        }
    }
#endif
}
