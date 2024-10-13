#include "_ds_.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define PYSTR_CAPACITY 16
#define pystr_calc_capacity(len, cap) ((cap) * (((len) + (cap)) / (cap)))

typedef struct PyStr
{
  char *str;
  size_t len;
  size_t capacity;
} PyStr;

PyStr *pystr_new (const char *);
void pystr_del (const PyStr *);
PyStr *pystr_assign (PyStr *, const char *);
PyStr *pystr_add (PyStr *, const char *);
char *pystr_str (const PyStr *);
size_t pystr_len (const PyStr *);
size_t pystr_cap (const PyStr *);
void pystr_dump (const PyStr *);

int
main (void)
{
  PyStr *pystr;
  char *ss11 = "Hello, Nore";

  pystr = pystr_new (NULL);
  assert (pystr != NULL && "pystr_new failed");
  assert (pystr_len (pystr) == 0 && pystr->capacity == PYSTR_CAPACITY
          && pystr->str != NULL);
  pystr_dump (pystr);

  pystr_assign (pystr, "Hello, Nore");
  pystr_dump (pystr);

  pystr_assign (pystr, "Hello, Nore, after 15 aaaaaaaaaaaaaaa");
  pystr_dump (pystr);
  pystr_del (pystr);

  pystr = pystr_new ("Hello, Nore");
  pystr_dump (pystr);
  pystr_del (pystr);

  pystr = pystr_new ("");
  assert (pystr_len (pystr) == 0 && pystr->capacity == PYSTR_CAPACITY
          && pystr->str != NULL);
  pystr_dump (pystr);

  pystr_add (pystr, ss11);
  pystr_add (pystr, "aaaa");
  pystr_dump (pystr);
  assert (pystr_cap (pystr) == PYSTR_CAPACITY);

  pystr_assign (pystr, ss11);
  pystr_dump (pystr);
  assert (pystr_cap (pystr) == PYSTR_CAPACITY);
  pystr_del (pystr);

  return 0;
}

char *
pystr_str (const PyStr *pystr)
{
  return pystr->str;
}

size_t
pystr_len (const PyStr *pystr)
{
  return pystr->len;
}

size_t
pystr_cap (const PyStr *pystr)
{
  return pystr->capacity;
}

void
pystr_dump (const PyStr *pystr)
{
  assert (pystr != NULL && "pystr should not be null");
  printf ("pystr@%p: capacity=%zu len=%zu str=%s\n", pystr, pystr->capacity,
          pystr->len, pystr->str);
}

PyStr *
pystr_new (const char *ss)
{
  PyStr *pystr;

  pystr = calloc (1, sizeof (*pystr));
  if (pystr == NULL)
    return NULL;
  pystr_assign (pystr, ss);
  return pystr;
}

void
pystr_del (const PyStr *pystr)
{
  assert (pystr != NULL && "pystr should not be null");
  free ((void *)pystr->str);
  free ((void *)pystr);
}

PyStr *
pystr_assign (PyStr *pystr, const char *ss)
{
  size_t len;
  size_t capacity;
  char *str;

  assert (pystr != NULL && "pystr should not be null");

  len = (ss == NULL) ? 0 : strlen (ss);
  capacity = pystr_calc_capacity (len, PYSTR_CAPACITY);
  str = realloc (pystr->str, capacity);
  if (str == NULL)
    return NULL;
  pystr->str = str;
  pystr->capacity = capacity;
  pystr->len = len;
  if (pystr->len == 0)
    pystr->str[0] = '\0';
  else
    strncpy (pystr->str, ss, pystr->len + 1);
  return pystr;
}

PyStr *
pystr_add (PyStr *pystr, const char *ss)
{
  size_t len;
  size_t capacity;
  char *str;

  assert (pystr != NULL && "pystr should not be null");

  if (ss == NULL)
    return NULL;

  len = strlen (ss);
  if (len == 0)
    return pystr;

  capacity = pystr_calc_capacity (pystr->len + len, PYSTR_CAPACITY);
  str = pystr->str;
  str = realloc (str, capacity);
  if (str == NULL)
    return NULL;
  pystr->str = str;

  if (len > 0)
    strncpy (pystr->str + pystr->len, ss, len + 1);

  pystr->len += len;
  pystr->capacity = capacity;
  return pystr;
}
